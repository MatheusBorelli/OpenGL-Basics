gcc src/main.c -o main -lglfw3 -lgdi32 -lopengl32 -lglew32 -lglu32

glfw3 - é a biblioteca que facilita a criação de janelas evitando configurar tudo do win32api.

gdi32 - Deve ir antes de opengl para exportar as funções de interface do dispositivo gráfico, permitindo desenhar no display de video.

opengl32 - Api grafica a ser utilizada.

glew32 - Pega do driver de video as funçoes do opengl

glu32 - biblioteca de utilitarios para o openGl