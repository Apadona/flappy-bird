#pragma once

#include <glad/glad.h>

#include <engine_pch.hpp>

enum class TextureType
{
    INVALID, // when the texture is not set ( default constructor ).

    TEXTURE_1D,
    TEXTURE_2D,
    TEXTURE_3D,
    TEXTURE_ARRAY_1D,
    TEXTURE_ARRAY_2D,
    TEXTURE_CUBEMAP,
    TEXTURE_ARRAY_CUBE_MAP
};

enum class TextureFormat
{
    INVALID,
    RGB,
    RGBA
};

enum class TextureFiltering
{
    NEAREST,
    LINEAR
};

enum class TextureWrapping
{
    REPEAT,
    MIRRORED_REPEAT,
    CLAMP_TO_EDGE,
    CLAMP_TO_BORDER
};

class Texture
{
    friend class Renderer;
    friend class TextureManager;

    public:
        static Texture* create( const std::string& texture_file_path );
        
        Texture() = default;
        Texture( const std::string& texture_file_path );
        Texture( TextureType type, GLint width, GLint height, unsigned char* data, TextureFormat format );
        Texture( Texture&& other );

        Texture& operator=( Texture&& ohter );

        ~Texture();

        bool Create( const std::string& texture_file_path );
        bool Create( TextureType type, GLint width, GLint height, unsigned char* data, TextureFormat format );

        void SetFilteringMethod( TextureFiltering filtering_method )
        {
            m_filter_method = filtering_method;
        }

        void SetWrappingMethod( TextureWrapping wrapping_method )
        {
            m_wrap_method = wrapping_method;
        }

        operator bool() const;
        bool operator!() const;

        TextureType GetType() const { return m_type; }
        TextureFiltering GetFilteringMethod() const { return m_filter_method; }
        TextureWrapping GetWrappingMethod() const { return m_wrap_method; }
        GLint GetSizeX() const { return m_width; }
        GLint GetSizeY() const { return m_height; }
        const unsigned char* GetData() const { return m_data; }

    private:
        void Bind( bool bind = true );

    private:
        GLuint m_id = 0;
        bool m_is_bound = false;
        
        TextureType m_type = TextureType::TEXTURE_2D;
        TextureFormat m_format = TextureFormat::RGB;
        GLint m_width = 0, m_height = 0;
        unsigned char* m_data = nullptr;

        TextureFiltering m_filter_method = TextureFiltering::LINEAR;
        TextureWrapping m_wrap_method = TextureWrapping::REPEAT;

        //static Texture default_white_texture;
};