#include "App.hpp"

App::App()
{
  Engine::Log("Object Made");
}
App::~App()
{
  Engine::Log("Object Destroyed");
}

void App::Run()
{
  if (appState == AppState::ON)
    Engine::FatalError("App already running.");

  Engine::Init();

  unsigned int windowFlags = 0;

  // windowFlags |= Engine::WindowFlags::FULLSCREEN;

  // windowFlags |= Engine::WindowFlags::BORDERLESS;

  window.Create("Engine", 800, 600, windowFlags);

  Load();

  appState = AppState::ON;

  Loop();
}

void App::Load()
{
  // build and compile our shader program
  // ------------------------------------
  shader.Compile("assets/shaders/3.3.shader.vs","assets/shaders/3.3.shader.fs");
  //shader.AddAttribute("ourColor");
  shader.Link();
  

  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  float vertices[] = {
      // positions                // color
      0.667f, 0.402f, 0.0f,       0.0f, 0.0f, 0.0f,
      0.465f, 0.314f, 0.0f,       0.0f, 0.0f, 0.0f,
      0.186f, 0.38f, 0.0f,        0.0f, 0.0f, 0.0f,
      0.0f, 0.39f, 0.0f,          0.0f, 0.0f, 0.0f,
      -0.186f, 0.38f, 0.0f,       0.0f, 0.0f, 0.0f,
      -0.465f, 0.314f, 0.0f,      0.0f, 0.0f, 0.0f,
      -0.667f, 0.402f, 0.0f,      0.0f, 0.0f, 0.0f,
      -0.873f, 0.486f, 0.0f,      0.0f, 0.0f, 0.0f,
      -0.748f, 0.199f, 0.0f,      0.0f, 0.0f, 0.0f,
      -0.911f, 0.077f, 0.0f,      0.0f, 0.0f, 0.0f,
      -0.783f, -0.063f, 0.0f,     0.5f, 0.5f, 0.5f,
      -0.606f, -0.214f, 0.0f,     0.5f, 0.5f, 0.5f,
      -0.478f, -0.301f, 0.0f,     0.5f, 0.5f, 0.5f,
      -0.367f, -0.368f, 0.0f,     0.5f, 0.5f, 0.5f,
      -0.245f, -0.423f, 0.0f,     0.5f, 0.5f, 0.5f,
      -0.147f, -0.46f, 0.0f,      0.5f, 0.5f, 0.5f,
      -0.051f, -0.487f, 0.0f,     0.5f, 0.5f, 0.5f,
      0.0f, -0.494f, 0.0f,        0.5f, 0.5f, 0.5f,
      0.051f, -0.487f, 0.0f,      0.5f, 0.5f, 0.5f,
      0.147f, -0.46f, 0.0f,       0.5f, 0.5f, 0.5f,
      0.245f, -0.423f, 0.0f,      0.5f, 0.5f, 0.5f,
      0.367f, -0.368f, 0.0f,      0.5f, 0.5f, 0.5f,
      0.478f, -0.301f, 0.0f,      0.5f, 0.5f, 0.5f,
      0.606f, -0.214f, 0.0f,      0.5f, 0.5f, 0.5f,
      0.783f, -0.063f, 0.0f,      0.5f, 0.5f, 0.5f,
      0.911f, 0.077f, 0.0f,       0.0f, 0.0f, 0.0f,
      0.748f, 0.199f, 0.0f,       0.0f, 0.0f, 0.0f,
      0.873f, 0.486f, 0.0f,       0.0f, 0.0f, 0.0f,
      0.667f, 0.402f, 0.0f,       0.0f, 0.0f, 0.0f,
  };

  // unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  // color
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
  // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
  glBindVertexArray(0);

  // wireframe
  glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
  // fill
  // glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
}

void App::Loop()
{
  while (appState == AppState::ON)
  {
    Update();
    Draw();
    // Get SDL to swap our buffer
    window.SwapBuffer();
    LateUpdate();
    FixedUpdate(0.0f);
    InputUpdate();
  }
}
void App::Update() {}
void App::Draw()
{
  glClear(GL_COLOR_BUFFER_BIT);

  // be sure to activate the shader before any calls to glUniform
  shader.Use();

  // update shader uniform
  //double  timeValue = SDL_GetTicks() / 1000;
  //float greenValue = static_cast<float>(sin(timeValue) / 2.0 + 0.5);
  //int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
  //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

  // render the triangle
  glBindVertexArray(VAO);
  glDrawArrays(GL_LINE_LOOP, 0, 28);
  glBindVertexArray(0);

  shader.UnUse();
}

void App::LateUpdate() {}
void App::FixedUpdate(float _delta_time) {}
void App::InputUpdate()
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
    case SDL_QUIT:
      appState = AppState::OFF;
      break;
    case SDL_MOUSEMOTION:
      break;
    case SDL_KEYUP:
      break;
    case SDL_KEYDOWN:
      break;
    }
  }
}