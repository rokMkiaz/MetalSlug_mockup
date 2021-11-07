#include <cassert>    //주장하다
#include <d3d11.h>

#include"Pipeline.h"


#ifdef NDEBUG   
#define MUST(Expression) (      (         (Expression)))

#else
#define MUST(Expression) (assert(SUCCEEDED(Expression)))
#endif


//Engine 발생한 cpp를 필요한 곳에 중계해주는 곳
namespace Engine::Rendering::Pipeline
{
    namespace
    {
        ID3D11Device        * Device;        
        ID3D11DeviceContext * DeviceContext; 
        
        IDXGISwapChain      * SwapChain;

      

        namespace Buffer
        {
            ID3D11Buffer* Vertex;            
            //ID3D11Buffer* Index; 사용함에 있어 사실 필요없음
            ID3D11Buffer* Constant[3];
        }

        ID3D11RenderTargetView* RenderTargetView;

        //파이프라인에서 우회하여 사용이 가능하지만 직접적으로 다룰려고 변수를 남겨둔것이다.
    }
    namespace String  // 폰트
    {
        void Render(HFONT const hFont, LPCSTR const string, COLORREF const color, SIZE const& size, POINT const& center)
        {
            IDXGISurface1* Surface = nullptr; //DXGI Surface1.1 ver

            MUST(SwapChain->GetBuffer(0, IID_PPV_ARGS(&Surface)));
            {
                HDC hDC = HDC();

                MUST(Surface->GetDC(false, &hDC));
                {
                    SelectObject(hDC, hFont);

                    SetTextColor(hDC, color);

                    RECT Area = RECT();

                    Area.left   = center.x - size.cx / 2;
                    Area.top    = center.y - size.cy / 2;
                    Area.right  = center.x + size.cx / 2;
                    Area.bottom = center.y + size.cy / 2;

                    UINT const Format = DT_WORDBREAK/*수평을 넘칠경우 내린다*/ | DT_NOPREFIX | DT_EDITCONTROL | DT_NOFULLWIDTHCHARBREAK;
                    
                    DrawText(hDC, string, ~'\0', &Area, Format); //텍스트를 그리는 부분
                }
                MUST(Surface->ReleaseDC(nullptr));
            }
            Surface->Release();

            DeviceContext->OMSetRenderTargets(1, &RenderTargetView, nullptr);
        }
    }
    namespace Texture
    {
        struct Handle final
        {
            ID3D11Texture2D          * const Texture2D;
            ID3D11ShaderResourceView * const ShaderResourceView;
        };


        void Create(Handle*& handle, SIZE const& size, BYTE const* const data)
        {
            D3D11_TEXTURE2D_DESC Descriptor
            {
                static_cast<UINT>(size.cx),
                static_cast<UINT>(size.cy),
                1,
                1,
                DXGI_FORMAT_B8G8R8A8_UNORM,
                1,
                0,
                D3D11_USAGE_IMMUTABLE,
                D3D11_BIND_SHADER_RESOURCE
            };

            UINT const BPP = 32;
            D3D11_SUBRESOURCE_DATA const Subresource
            {
                data,
                size.cx * (BPP / 8)

            };
            ID3D11Texture2D* Texture2D = nullptr;
            MUST(Device->CreateTexture2D(&Descriptor, &Subresource, &Texture2D));

            ID3D11ShaderResourceView* ShaderResourceView = nullptr;
            MUST( Device->CreateShaderResourceView(Texture2D, nullptr, &ShaderResourceView));
       
            handle = new Handle
            {
                Texture2D,
                ShaderResourceView
            };
        
        }

        void Render(Handle const* const& handle, RECT const& area)
        {
            DeviceContext->PSSetShaderResources(0, 1, &handle->ShaderResourceView);
            {
                D3D11_MAPPED_SUBRESOURCE Subresource = D3D11_MAPPED_SUBRESOURCE();

                MUST(DeviceContext->Map(Buffer::Vertex, 0, D3D11_MAP_WRITE_DISCARD, 0, &Subresource));
                {
                    float const Coordinates[4][2]
                    {
                        {static_cast<float>(area.left), static_cast<float>(area.top) },
                        {static_cast<float>(area.right), static_cast<float>(area.top) },
                        {static_cast<float>(area.left),  static_cast<float>(area.bottom) },
                        {static_cast<float>(area.right), static_cast<float>(area.bottom) }
                    };

                    memcpy_s(Subresource.pData, Subresource.RowPitch, Coordinates, sizeof(Coordinates));
                }
                DeviceContext->Unmap(Buffer::Vertex, 0);
            }

            DeviceContext->Draw(4, 0);
        }
        

        void Delete(Handle* const& handle)
        {
            handle->ShaderResourceView->Release();
            handle->Texture2D->Release();

            delete handle;
        }
    }
    
    namespace Transform
    {
        template<Type type>
        void Update(Matrix const& matrix)
        {
            UINT const index = static_cast<UINT>(type);
            D3D11_MAPPED_SUBRESOURCE Subresource = D3D11_MAPPED_SUBRESOURCE();

            MUST(DeviceContext->Map(Buffer::Constant[index], 0, D3D11_MAP_WRITE_DISCARD, 0, &Subresource));
            {

                memcpy_s(Subresource.pData, Subresource.RowPitch, matrix, sizeof(matrix));
            }
            DeviceContext->Unmap(Buffer::Vertex, 0);
        }

        template void Update<Type::World>(Matrix const&);
        template void Update<Type::View>(Matrix const&);
        template void Update<Type::Projection>(Matrix const&);

    }
    

    void  Procedure
    (HWND const hWindow,
        UINT const uMessage,
        WPARAM const wParameter,
        LPARAM const lParameter
        /*W,L PARAM메세지별 세부 정보 정확한 내용은 내부적으로 나뉘어져있음*/
    )

    {
        switch (uMessage)
        {

        case WM_CREATE:
        {
            {

                DXGI_SWAP_CHAIN_DESC Descriptor = DXGI_SWAP_CHAIN_DESC(); //0인것들 삭제

                Descriptor.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
                Descriptor.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
                Descriptor.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
                Descriptor.SampleDesc.Count = 1;
                Descriptor.SampleDesc.Quality = 0;
                Descriptor.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
                Descriptor.BufferCount = 1;
                Descriptor.OutputWindow = hWindow;
                Descriptor.Windowed = true;
                Descriptor.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
                Descriptor.Flags = DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE; //Resize


                MUST(D3D11CreateDeviceAndSwapChain /*디바이스와 스왑체인 동시생성*/
                (
                    nullptr,
                    D3D_DRIVER_TYPE_HARDWARE,
                    nullptr,
                    D3D11_CREATE_DEVICE_SINGLETHREADED,
                    nullptr,
                    0,
                    D3D11_SDK_VERSION,
                    &Descriptor,
                    &SwapChain,
                    &Device,
                    nullptr,
                    &DeviceContext
                ));

            }
            {
#include "Shader/Bytecode/Vertex.h"

                {

                    D3D11_INPUT_ELEMENT_DESC const Descriptor[2]
                    {
                        { "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0 },
                        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 1 }
                    };


                    ID3D11InputLayout* InputLayout = nullptr;

                    MUST(Device->CreateInputLayout
                    (
                        Descriptor,
                        2,
                        Bytecode,/*지정한색상과, VS내부 내용과 같은 주소를 넣어야함*/
                        sizeof(Bytecode),  /*포인터의 사이즈*/
                        &InputLayout
                    ));

                    DeviceContext->IASetInputLayout(InputLayout);

                    InputLayout->Release();
                }
                {
                    ID3D11VertexShader* VertexShader = nullptr;


                    MUST(Device->CreateVertexShader
                    (
                        Bytecode,
                        sizeof(Bytecode),
                        nullptr,/*Classlinkage hlsl에서 class생성이 가능 상속하여 동적쉐이딩(업케스팅) 링킹 사용할때 사용*/
                        &VertexShader
                    ));

                    DeviceContext->VSSetShader(VertexShader, nullptr, 0);

                    VertexShader->Release();
                }

            }
            {
#include"Shader/Bytecode/Pixel.h"

                {
                    ID3D11PixelShader* PixelShader = nullptr;

                    MUST(Device->CreatePixelShader
                    (
                        Bytecode,
                        sizeof(Bytecode),
                        nullptr,
                        &PixelShader
                    ));

                    DeviceContext->PSSetShader(PixelShader, nullptr, 0);

                    PixelShader->Release();
                }


            }

            {//Primitive Topology IA관련 사진 참조
                DeviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
            }

            {//Vertex Buffer - 위치


                float const Coordinates[4][2] //정점좌표
                {
                     {-0.5f, +0.5f },{+0.5f, +0.5f },
                     {-0.5f, -0.5f },{+0.5f, -0.5f }
                };

                D3D11_BUFFER_DESC const Descriptor
                {
                    sizeof(Coordinates),
                    D3D11_USAGE_IMMUTABLE,
                    D3D11_BIND_VERTEX_BUFFER,
                    0
                };


                D3D11_SUBRESOURCE_DATA Subresource
                {
                    Coordinates

                };


                ID3D11Buffer* Buuffer = nullptr;

                MUST(Device->CreateBuffer(&Descriptor, &Subresource, &Buuffer));

                UINT const Stride[] = { sizeof(*Coordinates) };
                UINT const Offset[] = { 0 };

                DeviceContext->IASetVertexBuffers(0, 1, &Buuffer, Stride/*Strides:버퍼 당vertex하나의 크기*/, Offset/*각버퍼별 생략할 버퍼수*/);
                //Pipeline에 버퍼를 결합 DX11기준 32개까지 가능 기본적으로 전부 배열로 처리하므로 포인트로 사용함.

            }
            {//Vertex Buffer - 색상

                D3D11_BUFFER_DESC const Descriptor
                {
                    sizeof(float[4][2]),
                    D3D11_USAGE_DYNAMIC,
                    D3D11_BIND_VERTEX_BUFFER,
                    D3D11_CPU_ACCESS_WRITE
                };




                MUST(Device->CreateBuffer(&Descriptor, nullptr, &Buffer::Vertex));//버퍼생성

                UINT const Stride[] = { sizeof(float[2]) };
                UINT const Offset[] = { 0 };

                DeviceContext->IASetVertexBuffers(1, 1, &Buffer::Vertex, Stride/*Strides:버퍼 당vertex하나의 크기*/, Offset/*각버퍼별 생략할 버퍼수*/);
                //Pipeline에 버퍼를 결합 DX11기준 32개까지 가능 기본적으로 전부 배열로 처리하므로 포인트로 사용함.

            }
            {

                D3D11_BUFFER_DESC const Descriptor
                {
                    sizeof(float[4][4]),
                    D3D11_USAGE_DYNAMIC,
                    D3D11_BIND_CONSTANT_BUFFER,
                    D3D11_CPU_ACCESS_WRITE
                };



                for (UINT u = 0; u < 3; ++u)
                {
                    MUST(Device->CreateBuffer(&Descriptor, nullptr, &Buffer::Constant[u]));
                }
                DeviceContext->VSSetConstantBuffers(0, 3, Buffer::Constant);
            }



            return;

        }


        case WM_APP:
        {

            MUST(SwapChain->Present(0, 0));

            float const Color[4]{ 0.0f,0.0f,0.0f,1.0f };

            DeviceContext->ClearRenderTargetView(RenderTargetView, Color);


            return;
        }
        case WM_DESTROY:
        {
            DeviceContext->ClearState();// pipeline 초기화 결합된 과정 전부 제거 

            RenderTargetView->Release();

            for (UINT u = 0; u < 3; ++u)
            {
                Buffer::Constant[u]->Release();
            }
            Buffer::Vertex->Release();

            SwapChain->Release();

            DeviceContext->Release();
            Device->Release();



            return;
        }
        case WM_SIZE:
        {
            {
                D3D11_VIEWPORT  Viewport
                {
                    0.0f,
                    0.0f,
                    static_cast<float>LOWORD(lParameter),
                    static_cast<float>HIWORD(lParameter),
                    0.0f,
                    0.0f
                };

                DeviceContext->RSSetViewports(1, &Viewport);

            }


            {


                if (RenderTargetView != nullptr)
                {
                    RenderTargetView->Release();
                    /*
                      resizebuffer 제약조건
                      SwapChain에 연계된 어떤것도 없어야 생성가능하기에 Release를 해주는것
                    */
                    MUST(SwapChain->ResizeBuffers
                    (
                        1,
                        LOWORD(lParameter),
                        HIWORD(lParameter),
                        DXGI_FORMAT_R8G8_B8G8_UNORM,
                        DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE

                    ));
                }
                {
                    ID3D11Texture2D* Texture2D = nullptr;

                    MUST(SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&Texture2D))); //IID_PPV_ARGS(&Texture2D)매크로 형식
                    {
                        IDXGISurface1* Surface = nullptr;
                        MUST(Texture2D->QueryInterface(IID_PPV_ARGS(&Surface))); // 해당 인터페이스를 가지고 있다면 받아온다
                        {//텍스트 배경을 투명으로 설정하는 구역
                            HDC hDC = HDC();

                            MUST(Surface->GetDC(false, &hDC));
                            {
                                SetBkMode(hDC, TRANSPARENT);
                            }
                            MUST(Surface->ReleaseDC(nullptr));

                        }
                        Surface->Release();
                        MUST(Device->CreateRenderTargetView(Texture2D, nullptr, &RenderTargetView));
                    }
                    Texture2D->Release();

                    DeviceContext->OMSetRenderTargets(1, &RenderTargetView, nullptr/*2차원이어서 널*/);

                }
            }
            return;
        }



        }

    }
}


