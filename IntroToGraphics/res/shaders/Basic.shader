    #shader vertex
    #version 410 core
                                
    layout(location = 0) in vec4 position;
    layout(location = 1) in vec2 texCoord;
                                
    void main() 
    { 
      gl_Position = position;  
      v_textCoord = texCoord;
    };

    #shader fragment
    #version 410 core
                                 
    layout(location = 0) out vec4 color;
           
    in vec2 v_textCoord;

    uniform vec4 u_color;
    uniform sampler2D u_texture;

    void main()
    {
        vec4 texColor = texture(u_texture, v_textCoord)
        color = texColor; 
    };