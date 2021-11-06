
#include<Windows.h>

#include<cmath>
#include<map>
#include<string>

#include "Resource.h"
#include"Time.h"

#include "Pipeline.h"
#include "FreeImage.h"
#include "Rendering.h"


namespace Engine::Rendering
{

    namespace Pipeline { void Procedure(HWND const, UINT const, WPARAM const, LPARAM const); }

      namespace
      {
       


          inline Matrix<4, 4> Translation(Vector<2>const& location)
          {
              return Matrix<4, 4>
              {
                  1, 0, 0, location[0],
                  0, 1, 0, location[1],
                  0, 0, 1, 0,
                  0, 0, 0, 1
              };
          }
          inline Matrix<4, 4> Rotation(float const& angle)
          {
              float const radian = angle * (3.14159265f / 180.0f);

              return Matrix<4, 4>
              {
                   cos(radian), -sin(radian), 0, 0,
                   sin(radian),  cos(radian), 0, 0,
                             0,            0, 1, 0,
                             0,            0, 0, 1
              };
          }
          inline Matrix<4, 4> Scale(Vector<2>const& length)
          {
              return Matrix<4, 4>
              {
                  length[0],         0, 0, 0,
                  0        , length[1], 0, 0,
                  0        ,         0, 1, 0,
                  0        ,         0, 0, 1
              };
          }
    
      }

      void Camera::Set() const
      {
          using namespace Pipeline;
          {
              Matrix<4, 4> const View = Rotation(-Angle) * Translation(-Location);
    
              Transform::Update<Transform::Type::View>
                  (
                      reinterpret_cast<Transform::Matrix const&>(View)
                  );

              Matrix<4, 4> const projection
              {
                  2 / Sight[0],            0, 0,  0,
                             0, 2 / Sight[1], 0,  0,
                             0,            0, 1,  0,
                             0,            0, 0,  1,

              };


              Transform::Update<Transform::Type::Projection>
                  (
                      reinterpret_cast<Transform::Matrix const&>(projection)
                  );
          }
      }

      namespace Text
      {

          void Import(std::string const& file)
          {
              AddFontResourceEx(file.data(), FR_PRIVATE | FR_NOT_ENUM, nullptr);
          }
          void Component::Render()
          {

              LOGFONT font = LOGFONT(); //폰트 디스크립터
              font.lfHeight = Font.Size; //폰트사이즈
              
           
              font.lfWeight         =Font.Bold==false? FW_NORMAL : FW_BOLD;
              font.lfItalic         =Font.Italic    ; // 기울어짐
              font.lfUnderline      =Font.Underlined ;
              font.lfStrikeOut      =Font.StructOut;//언더라인
              font.lfCharSet        = DEFAULT_CHARSET ;
              strcpy_s(font.lfFaceName, LF_FACESIZE, Font.Name);

              HFONT const hFont = CreateFontIndirect(&font);

              COLORREF const color = RGB(Color.Red, Color.Green, Color.Blue);

              SIZE const size
              {
                  static_cast<LONG>(Length[0]),
                  static_cast<LONG>(Length[1])
              };
              POINT const center
              {
                   static_cast<LONG>(Location[0]),
                   static_cast<LONG>(Location[1])
              };

              Pipeline::String::Render(hFont, Text, color, size, center);

              DeleteObject(hFont);
          }

      }

      namespace Image
      {
          namespace
          {
              class Descriptor final
              {
              public:
                  Pipeline::Texture::Handle* const Handle;

              public:
                  SIZE const Size;
              };

              std::map<std::string const, Descriptor const> Storage;

              void Import(std::string const& file)
              {
                  FIBITMAP* bitmap = FreeImage_Load(FreeImage_GetFileType(file.data()), file.data());
                  {
                      if (FreeImage_GetBPP(bitmap) != 32)
                      {
                          FIBITMAP* const previous = bitmap;

                          bitmap = FreeImage_ConvertTo32Bits(bitmap);

                          FreeImage_Unload(previous);
                      }

                      FreeImage_FlipVertical(bitmap);
                  }
                  {
                      Pipeline::Texture::Handle* handle = nullptr;
                      {
                          SIZE const size
                          {
                              static_cast<LONG>(FreeImage_GetWidth(bitmap)),
                              static_cast<LONG>(FreeImage_GetHeight(bitmap))
                          };

                          BYTE const* const data = FreeImage_GetBits(bitmap);

                          Pipeline::Texture::Create(handle, size, data);
                      }
                      {
                          UINT const top = static_cast<UINT>(file.find_first_of('/') + sizeof(char));
                          UINT const bot = static_cast<UINT>(file.find_last_of('.'));

                          SIZE const size
                          {
                              static_cast<LONG>(FreeImage_GetWidth(bitmap)),
                              static_cast<LONG>(FreeImage_GetHeight(bitmap))
                          };

                          Descriptor const descriptor
                          {
                              handle,
                              size
                          };

                          Storage.try_emplace(file.substr(top, bot - top), descriptor);
                      }
                  }
                  FreeImage_Unload(bitmap);
              }
          }

          void Component::Render()
          {
              using namespace Pipeline;
              {
                  Matrix<4, 4> const world = Translation(Location) * Rotation(Angle) * Scale(Length);

                  Transform::Update<Transform::Type::World>
                      (
                          reinterpret_cast<Transform::Matrix const&>(world)
                          );
              }
              {
                  Descriptor const& descriptor = Storage.at(Name);

                  RECT const area
                  {
                      descriptor.Size.cx * 0, descriptor.Size.cy * 0,
                      descriptor.Size.cx * 1, descriptor.Size.cy * 1
                  };

                  Pipeline::Texture::Render(descriptor.Handle, area);
              }
          }
      }
      namespace Animation
      {
          namespace
          {
              class Descriptor final 
              {
              public:
                  Pipeline::Texture::Handle* const Handle;
              public:
                  UINT const Motion;
                  SIZE const Frame;
              };

              std::map<std::string const, Descriptor const> Storage; // 이름을 통해 해당 클래스 생성
             
              void Import(std::string const& file)
              {
           

                      FIBITMAP* bitmap = FreeImage_Load(FreeImage_GetFileType(file.data()), file.data());
                      {
                          if (FreeImage_GetBPP(bitmap) != 32)
                          {
                              FIBITMAP* const previous = bitmap;//주소 삭제를 위해

                              bitmap = FreeImage_ConvertTo32Bits(bitmap); //32비트아닐경우 변환하여 넣어준다

                              FreeImage_Unload(previous);

                          }
                          FreeImage_FlipVertical(bitmap);
                      }
                      
                      { // 핸들 생성
                          Pipeline::Texture::Handle* handle = nullptr;
                          {
                              SIZE const size
                              {
                                  static_cast<LONG>(FreeImage_GetWidth(bitmap)),
                                  static_cast<LONG>(FreeImage_GetHeight(bitmap))
                              };
                              BYTE const* const data = FreeImage_GetBits(bitmap);

                              Pipeline::Texture::Create(handle, size, data);
                          }
                          {//파일명에서 모션수 추출
                              UINT const top = static_cast<UINT>(file.find_first_of('/') + sizeof(char));
                              UINT const mid = static_cast<UINT>(file.find_last_of('[') );
                              UINT const bot = static_cast<UINT>(file.find_last_of(']') );

                              UINT const motion = std::atoi(file.substr(mid+sizeof(char),bot).data());//사이에있는 숫자 전부를 정수로 읽겠다.
                              
                              SIZE const frame
                              {
                                  static_cast<LONG>(FreeImage_GetWidth(bitmap) / motion),
                                  static_cast<LONG>(FreeImage_GetHeight(bitmap))
                              };

                              Descriptor const descriptor
                              {
                                  handle,
                                  motion,
                                  frame
                              };
                              
                              Storage.try_emplace(file.substr(top, mid-top),descriptor); //몇글자 추출하는 함수  mid='[' 전까지 추출->애니매이션 파일의 이름
                          }
                      }
                      FreeImage_Unload(bitmap);
    

              }

             
          }
          void Component::Render()     // 월드갱신, 택스처좌표 갱신
          {
              using namespace Pipeline;
              {
                  Matrix<4, 4> const world = Translation(Location) * Rotation(Angle) * Scale(Length);
                  

                  Transform::Update<Transform::Type::World>
                  (
                      reinterpret_cast<Transform::Matrix const&>(world)
                  );
              }
              {
                  Descriptor const& descriptor = Storage.at(Name);//디스크립터 함수와 맵을통해 구성한 정보와 연결시킴.


                  LONG const progress = static_cast<LONG>((Playback / Duration) * descriptor.Motion);
                          
                  RECT const area
                  {
                      descriptor.Frame.cx*( progress + Flipped),  descriptor.Frame.cy*0,
                      descriptor.Frame.cx*( progress + !Flipped), descriptor.Frame.cy*1
                  };
             

                  Rendering::Pipeline::Texture::Render(descriptor.Handle, area);

                  Playback  += Time::Get::Delta();
                  

                  if (Duration <= Playback)//해당조건은 반복을 조건
                  {
                      if (Repeatable == true)Playback = fmod(Playback, Duration);
                      else Playback=Duration;
                  }

                  
              }
          }
      }

    void Procedure(HWND const hWindow, UINT const uMessage, WPARAM const wParameter, LPARAM const lParameter)
    {
        switch (uMessage)
        {

        case WM_CREATE:    //생성직후 생성자와 같음, lParmeter로 CRATESTRUCT Window의 인자값이 포인터로 입력
        {
            Pipeline::Procedure(hWindow, uMessage, wParameter, lParameter);
    
            Resource::Import("Asset/Font", Text::Import);

            FreeImage_Initialise();
            {
                Resource::Import("Asset/Image", Image::Import);
                Resource::Import("Asset/Animation/Enemy", Animation::Import);
                Resource::Import("Asset/Animation/SlugFile", Animation::Import);
           
            }
            FreeImage_DeInitialise();

            
            


            return;
        }


        case WM_APP:
        {


            Pipeline::Procedure(hWindow, uMessage, wParameter, lParameter);

            return;
        }
        case WM_DESTROY: //창이 파괴 될때  소멸자와 동일
        {
            //Pipeline::Texture::Delete(handle);
            Pipeline::Procedure(hWindow, uMessage, wParameter, lParameter);
            PostQuitMessage(0); //프로그램 완전 종료를 위해 필요.

            return;
        }


        case WM_MOUSEWHEEL:  case WM_MOUSEHWHEEL: case WM_MOUSEMOVE:
        case WM_SYSKEYDOWN:  case WM_LBUTTONDOWN: case WM_LBUTTONUP:
        case WM_SYSKEYUP:    case WM_RBUTTONDOWN: case WM_RBUTTONUP:
        case WM_KEYDOWN:     case WM_MBUTTONDOWN: case WM_MBUTTONUP:
        case WM_KEYUP:       case WM_XBUTTONDOWN: case WM_XBUTTONUP:
        {



            return;
        }
        case WM_SIZE:
        {
            Pipeline::Procedure(hWindow, uMessage, wParameter, lParameter);
            return;
        }
        }
    }
}

