#pragma once

#include"Vector.h"

namespace Engine::Rendering
{
    class Camera final //Projection,view
    {
    public:
        void Set() const;

    public:  
        Vector<2>Location = Vector<2>();
        Vector<2>Sight = Vector<2>();
        float    Angle = 0.0f;

    };

    namespace Text
    {
        class Component final
        {
        public:
          
            void Render();

        public:
            char const* Text = nullptr;

            struct
            {
                char const* Name = nullptr;
                int  Size        = 0;
                bool Bold        = false;
                bool Italic      = false;
                bool Underlined  = false;
                bool StructOut   = false;
            }Font;

            struct
            {
                unsigned char Red   = 0;
                unsigned char Green = 0;
                unsigned char Blue  = 0;
                
            }Color;

        public:  
            Vector<2>Location = Vector<2>();
            Vector<2>Length = Vector<2>();
            float    Angle = 0.0f;
        };
    }

    namespace Image
    {
        class Component final
        {
        public:
            void Render();


        public:
            char const* Name = nullptr;

  
        public:  //Transform
            Vector<2>Location = Vector<2>();
            Vector<2>Length = Vector<2>();
            float    Angle = 0.0f;
        };


    }
    namespace Animation
    {
        class Component final
        {
        public:
            void Render();


        public:
            char const* Name = nullptr;

            float       Playback =0.0f;
            float       Duration =0.0f;
            bool        Repeatable = false;
            bool        Flipped    = false;
        public:  //Transform
            Vector<2>Location = Vector<2>();
            Vector<2>Length   = Vector<2>();
            float    Angle    = 0.0f;
        };

    
    }
}

