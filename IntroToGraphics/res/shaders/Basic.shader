    #shader vertex
    #version 410 core
                                
    //layout of our vertex buffer
    layout(location = 0) in vec4 position;
    layout(location = 1) in vec2 texCoord;
               
    //pass to fragment shader
    out vec2 v_textCoord;

    void main() 
    { 
      //set vertex position and texture position
      gl_Position = position;  
      v_textCoord = texCoord;
    };

    #shader fragment
    #version 410 core
                        
    
    layout(location = 0) out vec4 color;
           
    //passed from vertex shader
    in vec2 v_textCoord;

    //set from GLEW
    uniform vec4 u_color;
    uniform sampler2D u_texture;

    void main()
    {
        //get texture color
        vec4 texColor = texture(u_texture, v_textCoord);
        //combine texture and tint color
        color = texColor * u_color; 
    };