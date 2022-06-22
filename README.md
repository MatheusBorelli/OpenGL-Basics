# OpenGL-Basics
## Why i made this repo?

I made this repo to study OpenGL and learn how renderization works using [Cherno's Tutorials].


## Compilation

To compile this project just use the following command in terminal
```sh 
make all
```

## Known Issue

AMD drivers for openGL have poor support, so for many searching how to solve flicking textures problem in amd cards, I found that you can make an loop in [fragment shader] to solve this problem.  

## Libs

- [GLFW](https://www.glfw.org/) 

- [cglm](https://github.com/recp/cglm)

- [cimgui](https://github.com/cimgui/cimgui)

- [stb_image](https://github.com/nothings/stb)

## License

[MIT](LICENSE)

[Cherno's Tutorials]: https://www.youtube.com/playlist?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2
[fragment shader]: asset/shaders/BasicBatchRender.glsl
