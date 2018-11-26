// sous mac
// g++ -I/usr/local/include/ -lglfw -lGLEW projet2018.cpp -framework OpenGL -oprojet2018
// ./projet2018

// sous linux
// g++ -I/usr/local/include/ -I/public/ig/glm/ -c projet2018.cpp  -oprojet2018.o
// g++ -I/usr/local projet2018.o -lglfw  -lGLEW  -lGL  -oprojet2018
// ./projet2018

// Inclut les en-têtes standards
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;

#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#define GLM_FORCE_RADIANS
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

using namespace glm;

float ptime = 0.0f;
float vv = 1.5f;

float nbBands = 8.0f;

int N = 4;

int SMOOTHING_VALS = 1;
int SMOOTHING_VOLS = 1;

// gauss function
float gaussian( float x, float mu, float sigma ) {
  const float a = ( x - mu ) / sigma;
  return std::exp( -0.5 * a * a );
}


// compute a 1D kernel of gauss numbers
vector<float> computeGaussianKernel(int kernelRadius){
  vector<float> kernel(kernelRadius*2);

  //TO DO

  return kernel;
}


vector<float> smoothData(vector<float> &data, vector<float> &kernel){
  vector<float> smoothdata(data.size());
  vector<float> sums(data.size());

  // TO DO

  return smoothdata;
}


void loadData(string filename, vector<float> &vols, vector<float> &vals){
  ifstream file ( filename ); // declare file stream: http://www.cplusplus.com/reference/iostream/ifstream/
  string value;
  getline ( file, value, '\n' ); //skip first line

  float minval = 0.0f;
  float minvol = 0;
  float maxval = 0.0f;
  float maxvol = 0;
  while ( file.good() ) {
   // TO DO (read data file)
   float adjclose = 0.0f;
   float volume = 0.0f;

   vals.push_back(adjclose);
   vols.push_back(volume);
  }

  // on rajoute 2 fausses valeurs a la fin que l'on affichera pas .. mais qu'on utilisera pour normaliser !
  vals.push_back(minval);
  vals.push_back(maxval);
  vols.push_back(minvol);
  vols.push_back(maxvol);
}


GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){

  // Create the shaders
  GLuint VertexShaderID   = glCreateShader(GL_VERTEX_SHADER);
  GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

  // Read the Vertex Shader code from the file
  std::string VertexShaderCode;
  std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
  if(VertexShaderStream.is_open()){
    std::string Line = "";
    while(getline(VertexShaderStream, Line))
      VertexShaderCode += "\n" + Line;
    VertexShaderStream.close();
  }else{
    printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
    getchar();
    return 0;
  }

  // Read the Fragment Shader code from the file
  std::string FragmentShaderCode;
  std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
  if(FragmentShaderStream.is_open()){
    std::string Line = "";
    while(getline(FragmentShaderStream, Line))
      FragmentShaderCode += "\n" + Line;
    FragmentShaderStream.close();
  }

  GLint Result = GL_FALSE;
  int InfoLogLength;


  // Compile Vertex Shader
  printf("Compiling shader : %s\n", vertex_file_path);
  char const * VertexSourcePointer = VertexShaderCode.c_str();
  glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
  glCompileShader(VertexShaderID);

  // Check Vertex Shader
  glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if ( InfoLogLength > 0 ){
    std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
    glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
    printf("%s\n", &VertexShaderErrorMessage[0]);
  }



  // Compile Fragment Shader
  printf("Compiling shader : %s\n", fragment_file_path);
  char const * FragmentSourcePointer = FragmentShaderCode.c_str();
  glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
  glCompileShader(FragmentShaderID);

  // Check Fragment Shader
  glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if ( InfoLogLength > 0 ){
    std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
    glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
    printf("%s\n", &FragmentShaderErrorMessage[0]);
  }



  // Link the program
  printf("Linking program\n");
  GLuint ProgramID = glCreateProgram();
  glAttachShader(ProgramID, VertexShaderID);
  glAttachShader(ProgramID, FragmentShaderID);
  glLinkProgram(ProgramID);


  // Check the program
  glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
  glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if ( InfoLogLength > 0 ){
    std::vector<char> ProgramErrorMessage(InfoLogLength+1);
    glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
    printf("%s\n", &ProgramErrorMessage[0]);
  }


  glDetachShader(ProgramID, VertexShaderID);
  glDetachShader(ProgramID, FragmentShaderID);

  glDeleteShader(VertexShaderID);
  glDeleteShader(FragmentShaderID);

  return ProgramID;
}


int loadModelA(vector<float> &vecVols, vector<float> &vecVals, GLuint VertexArrayIDA){

  int bufSize = 100; // TODO

  GLfloat g_vertex_buffer_dataA[bufSize];
  GLfloat g_vertex_normal_dataA[bufSize]; // TODO: used in glBufferData !!!
  GLfloat g_vertex_color_dataA[bufSize];

  for(int i=0; i<bufSize; i++){
    g_vertex_buffer_dataA[i] = 0.654321;
    g_vertex_color_dataA[i]  = 0.654321;;
  }

  for (int i=0; i<N-1; i++){
    // TO DO
  }

  // on teste s'il ne reste pas notre valeur bizarre dans le tableau = on a pas oublie de cases !
  for(int i=0; i<bufSize; i++)
    if (g_vertex_buffer_dataA[i] > 0.654320 && g_vertex_buffer_dataA[i] < 0.654322)
      cout << i<<" EVIL IS IN THE DETAIL !" << endl ;

  glBindVertexArray(VertexArrayIDA);

  // This will identify our vertex buffer
  GLuint vertexbufferA;
  // Generate 1 buffer, put the resulting identifier in vertexbuffer
  glGenBuffers(1, &vertexbufferA);

  // The following commands will talk about our 'vertexbuffer' buffer
  glBindBuffer(GL_ARRAY_BUFFER, vertexbufferA);

    // Only allocate memory. Do not send yet our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_dataA)+sizeof(g_vertex_color_dataA)+sizeof(g_vertex_normal_dataA), 0, GL_STATIC_DRAW);

      // send vertices in the first part of the buffer
    glBufferSubData(GL_ARRAY_BUFFER, 0,                            sizeof(g_vertex_buffer_dataA), g_vertex_buffer_dataA);

    // send colors in the second part of the buffer
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_dataA), sizeof(g_vertex_color_dataA), g_vertex_color_dataA);

    // send bormals in the third part of the buffer
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_dataA)+sizeof(g_vertex_color_dataA), sizeof(g_vertex_normal_dataA), g_vertex_normal_dataA);

    // ici les commandes stockees "une fois pour toute" dans le VAO
    glVertexAttribPointer(
       0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
       3,                  // size
       GL_FLOAT,           // type
       GL_FALSE,           // normalized?
       0,                  // stride
       (void*)0            // array buffer offset
    );
    glEnableVertexAttribArray(0);

    glVertexAttribPointer( // same thing for the colors
      1,
      3,
      GL_FLOAT,
      GL_FALSE,
      0,
      (void*)sizeof(g_vertex_buffer_dataA));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer( // same thing for the normals
      2,
      3,
      GL_FLOAT,
      GL_FALSE,
      0,
      (void*)(sizeof(g_vertex_buffer_dataA)+sizeof(g_vertex_color_dataA)));
    glEnableVertexAttribArray(2);


  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // on desactive le VAO a la fin de l'initialisation
  glBindVertexArray (0);

  return sizeof(g_vertex_buffer_dataA)/(3*sizeof(float));
}



int loadModelB(vector<float> &vecVols, vector<float> &vecVals, GLuint VertexArrayIDB){

  int bufSize = 3*3*N; //TODO

  GLfloat g_vertex_buffer_dataB[bufSize]; // 4 triangles of 3 points with 3 coordinates each

  //cout<< "loadModelB " << (sizeof(g_vertex_buffer_dataB)/(sizeof(float)))<<" % "<<(3*3*4*(N))<<endl;
  for(int i=0; i<bufSize; i++)
    g_vertex_buffer_dataB[i] = 0.654321;

  // on rajoute des faces et de la hauteur a notre figure
  for (int i=0; i<N-1; i++){
    // TO DO
  }

  // TO DO

  for(int i=0; i<bufSize; i++)
    if (g_vertex_buffer_dataB[i] > 0.654320 && g_vertex_buffer_dataB[i] < 0.654322)
      cout << i<<" EVIL IS IN THE DETAIL !" << endl ;

  // This will identify our vertex buffer
  GLuint vertexbufferB;

  // on s'occupe du second VAO
  glBindVertexArray(VertexArrayIDB);
  glGenBuffers(1, &vertexbufferB);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbufferB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_dataB), 0, GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0,                            sizeof(g_vertex_buffer_dataB), g_vertex_buffer_dataB);
  glVertexAttribPointer(
       0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
       3,                  // size
       GL_FLOAT,           // type
       GL_FALSE,           // normalized?
       0,                  // stride
       (void*)0            // array buffer offset
    );
  glEnableVertexAttribArray(0);


  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // on desactive le VAO a la fin de l'initialisation
  glBindVertexArray (0);

  return sizeof(g_vertex_buffer_dataB)/(3*sizeof(float));
}


int main(){
  // for later printing
  std::cout << std::setprecision(5) << std::fixed;

  vector<float> kernel0 = computeGaussianKernel(SMOOTHING_VALS);

  for (int i = 0; i < kernel0.size(); i++)
    cout << i<<": " << kernel0[i] << endl;

  // Initialise GLFW
  if( !glfwInit() ) {
      fprintf( stderr, "Failed to initialize GLFW\n" );
      return -1;
  }  
  
  // Load data files
  /*
  vector<float> vols10;
  vector<float> vals10;

  vector<float> vols20;
  vector<float> vals20;

  vector<float> vols30;
  vector<float> vals30;

  vector<float> vols40;
  vector<float> vals40;

  loadData("data/AAPL.csv",  vols10, vals10);
  loadData("data/GOOGL.csv", vols20, vals20);
  loadData("data/AMZN.csv",  vols30, vals30);
  loadData("data/MSFT.csv",  vols40, vals40);
  N = vals10.size()-3;
  */

  // set window hints
  glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // On veut OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Pour rendre MacOS heureux ; ne devrait pas être nécessaire
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // On ne veut pas l'ancien OpenGL
  glfwWindowHint(GLFW_DEPTH_BITS, 24);

  // Ouvre une fenêtre et crée son contexte OpenGl
  GLFWwindow* window; // (Dans le code source qui accompagne, cette variable est globale)
  window = glfwCreateWindow( 1600, 768, "Projet 2018", NULL, NULL);
  if( window == NULL ){
      fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
      glfwTerminate();
      return -1;
  }

  glfwMakeContextCurrent(window); // Initialise GLEW
  glewExperimental=true; // Nécessaire dans le profil de base
  if (glewInit() != GLEW_OK) {
      fprintf(stderr, "Failed to initialize GLEW\n");
      return -1;
  }

  // Enable depth test
  glEnable(GL_DEPTH_TEST);

  // Accept fragment if it closer to the camera than the former one
  glDepthFunc(GL_LESS);
  glDepthRange(-1, 1);

  // Assure que l'on peut capturer la touche d'échappement enfoncée ci-dessous
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  // Bon maintenant on cree les IDs de VAO
  /*
  GLuint VertexArrayIDA1, VertexArrayIDB1;
  GLuint VertexArrayIDA2, VertexArrayIDB2;
  GLuint VertexArrayIDA3, VertexArrayIDB3;
  GLuint VertexArrayIDA4, VertexArrayIDB4;

  glGenVertexArrays(1, &VertexArrayIDA1);
  glGenVertexArrays(1, &VertexArrayIDB1);
  glGenVertexArrays(1, &VertexArrayIDA2);
  glGenVertexArrays(1, &VertexArrayIDB2);
  glGenVertexArrays(1, &VertexArrayIDA3);
  glGenVertexArrays(1, &VertexArrayIDB3);
  glGenVertexArrays(1, &VertexArrayIDA4);
  glGenVertexArrays(1, &VertexArrayIDB4);

  int m11 = loadModelA(vols10, vals10, VertexArrayIDA1);
  int m12 = loadModelB(vols10, vals10, VertexArrayIDB1);

  int m21 = loadModelA(vols20, vals20, VertexArrayIDA2);
  int m22 = loadModelB(vols20, vals20, VertexArrayIDB2);

  int m31 = loadModelA(vols30, vals30, VertexArrayIDA3);
  int m32 = loadModelB(vols30, vals30, VertexArrayIDB3);

  int m41 = loadModelA(vols40, vals40, VertexArrayIDA4);
  int m42 = loadModelB(vols40, vals40, VertexArrayIDB4);

  GLuint ProgramA        = LoadShaders( "projet2018A.vs", "projet2018A.fs" );
  GLint  uniform_...     = glGetUniformLocation(ProgramA, "...");
  GLint  uniform_...     = glGetUniformLocation(ProgramA, "...");
  ...

  GLuint ProgramB        = LoadShaders( "projet2018B.vs", "projet2018B.fs" );
  GLint  uniform_...     = glGetUniformLocation(ProgramB, "...");
  GLint  uniform_...     = glGetUniformLocation(ProgramB, "...");
  ...
  */

  do {
    // clear before every draw
    glClearColor( 1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*
    // Use our shader program
    glUseProgram(ProgramA);

    // onchange de matrice de projection : la projection orthogonale est plus propice a la visualization !
    //glm::mat4 projectionMatrix = glm::perspective(glm::radians(66.0f), 1024.0f / 768.0f, 0.1f, 200.0f);
    glm::mat4 projectionMatrix = glm::ortho( -1.0f, 1.0f, -1.0f, 1.0f, -6.f, 6.f );
    
    float angle = 0.0f; // TODO

    float camPos[3] = {1.2*cos(angle), 1.2*sin(angle), -0.5};
    glm::mat4 viewMatrix       = glm::lookAt(
                                  glm::make_vec3(camPos), // where is the camara
                                  vec3(0, 0, 0.4), //where it looks
                                  vec3(0, 0, 1) // head is up
                                );
    mat4 modelMatrix1      =  scale(glm::mat4(1.0f), glm::vec3(0.75f));
    modelMatrix1           =  translate(modelMatrix1, glm::vec3(0.0f, 0.3f, 0.0f));


    // on envoie les valeurs uniforme aux shaders
    glUniform...(...,  1, GL_FALSE, glm::value_ptr(viewMatrix));
    ....

    // on re-active les VAO avant d'envoyer les buffers
    glBindVertexArray(VertexArrayIDA1);
    glDrawArrays(GL_TRIANGLES, 0, m11);

    glBindVertexArray(VertexArrayIDA2);
    glDrawArrays(GL_TRIANGLES, 0, m21);

    glBindVertexArray(VertexArrayIDA3);
    glDrawArrays(GL_TRIANGLES, 0, m31);

    glBindVertexArray(VertexArrayIDA4);
    glDrawArrays(GL_TRIANGLES, 0, m41);
    */

    /*
    glUseProgram(ProgramB);
    glUniform...(...,  1, GL_FALSE, glm::value_ptr(viewMatrix));
    ...

    glBindVertexArray(VertexArrayIDB1);
    glDrawArrays(GL_TRIANGLES, 0, m12); // Starting from vertex 0 .. all the buffer

    glBindVertexArray(VertexArrayIDB2);
    glDrawArrays(GL_TRIANGLES, 0, m22);

    glBindVertexArray(VertexArrayIDB3);
    glDrawArrays(GL_TRIANGLES, 0, m32);

    glBindVertexArray(VertexArrayIDB4);
    glDrawArrays(GL_TRIANGLES, 0, m42);
    */

    // on desactive le VAO a la fin du dessin
    glBindVertexArray (0);

    // on desactive les shaders
    glUseProgram(0);

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();

    if (glfwGetKey(window, GLFW_KEY_E ) == GLFW_PRESS){
      //TO DO
    } else if (glfwGetKey(window, GLFW_KEY_D ) == GLFW_PRESS){
      //TO DO
    } else if (glfwGetKey(window, GLFW_KEY_R ) == GLFW_PRESS){
      //TO DO
    } else if (glfwGetKey(window, GLFW_KEY_F ) == GLFW_PRESS){
      //TO DO
    } else if ( glfwGetKey(window, GLFW_KEY_LEFT ) == GLFW_PRESS ){
      //TO DO
    } else if ( glfwGetKey(window, GLFW_KEY_RIGHT ) == GLFW_PRESS && SMOOTHING_VALS<32){
      //TO DO
    } else if ( glfwGetKey(window, GLFW_KEY_DOWN ) == GLFW_PRESS && SMOOTHING_VOLS>1){
      //TO DO
    } else if ( glfwGetKey(window, GLFW_KEY_UP ) == GLFW_PRESS && SMOOTHING_VOLS<32){
      //TO DO
    }

  } // Vérifie si on a appuyé sur la touche échap (ESC) ou si la fenêtre a été fermée
  while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 );
}
