#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "bed.h"
#include "shader.h"
#include "camera.h"
#include "basic_camera.h"
#include "pointLight.h"
#include "directionalLight.h"
#include "SpotLight.h"
#include "walls.h"
#include "bench.h"
#include "swing.h"
#include "stand.h"
#include "cube.h"
#include "stb_image.h"
#include "cylinderStand.h"
#include <iostream>
#include "sphere.h"
struct Point {
    float x;
    float y;
    float z;
};
//ride1
float dy = 0.0;
int flag = 4;

//shop

float dyShop = 0.0;
int flagShop = 4;

//swing
float dz = 0.0;
int swingFlag = 14;
//Ride2
float dx = 0.0;
int flagR2 = 5 ;

//seesaw

float dr = 0.0;
int flag_ss = 5;
//ride_3
float d_up = 0.0;
int flag3 = 5;

//Ride_4 extra
float drx = 0.0;
int flag_ex = 25;

float dy4 = 0.0;
int flag4 = 5;

//washroom
float door = 0.0;
int flag_door = 5;

//train
float dzt = 0.0;
int flag_train = 5; 

//Rocket
float ds = 0.0;
float ds1 = 0.0;
int flag_rkt = 5;

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax);
void processInput(GLFWwindow* window);

long long nCr(int n, int r);
void BezierCurve(double t, float xy[2], GLfloat ctrlpoints[], int L);
unsigned int hollowBezier(GLfloat ctrlpoints[], int L);

// settings
const unsigned int SCR_WIDTH = 1500;
const unsigned int SCR_HEIGHT = 800;

// modelling transform
float rotateAngle_X = 0.0;
float rotateAngle_Y = 0.0;
float rotateAngle_Z = 0.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 1.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;

/*---------------*/
vector<float> cntrlPoints
{
    -0.1200, 1.9950, 5.1000,
    -0.3150, 1.8950, 5.1000,
    -0.4600, 1.7800, 5.1000,
    -0.6000, 1.6600, 5.1000,
    -0.7050, 1.5650, 5.1000,
    -0.8500, 1.4550, 5.1000,
    -0.9550, 1.3800, 5.1000,
    -1.0550, 1.2850, 5.1000,
};

vector<float> cntrlPointsCylinder
{
-0.4500, 1.7950, 5.1000,
-0.4550, 1.4950, 5.1000,
-0.4550, 1.0000, 5.1000,
};

vector<float> cntrlPointsBasin
{
-0.7600, 1.5350, 5.1000,
-0.7250, 1.3950, 5.1000,
-0.6600, 1.3350, 5.1000,
-0.5500, 1.2750, 5.1000,
-0.4350, 1.2400, 5.1000,
-0.3300, 1.2100, 5.1000,
-0.2300, 1.1950, 5.1000,
-0.1650, 1.1550, 5.1000,
-0.1100, 1.0900, 5.1000,
-0.0900, 1.0050, 5.1000,
-0.0900, 0.9350, 5.1000,
-0.1000, 0.8450, 5.1000,
-0.1000, 0.7450, 5.1000,
-0.1050, 0.6400, 5.1000,
-0.1050, 0.5350, 5.1000,
-0.1150, 0.4400, 5.1000,
-0.1250, 0.3650, 5.1000,
0.2100, 0.4750, 5.1000,
};

vector<float> cntrlPtSeat
{
-0.9200, 1.5600, 5.1000,
-0.9150, 1.4150, 5.1000,
-0.8900, 1.2700, 5.1000,
-0.8250, 1.1400, 5.1000,
-0.6700, 1.0600, 5.1000,
-0.5050, 1.0050, 5.1000,
-0.3600, 0.9600, 5.1000,
-0.2300, 0.9300, 5.1000,
-0.0700, 0.9000, 5.1000,
0.2100, 0.8450, 5.1000,
};

vector<float> cntrlPtComodeBase
{
    -0.8000, 1.5500, 5.1000,
        -0.7750, 1.4650, 5.1000,
        -0.7150, 1.3850, 5.1000,
        -0.6300, 1.3200, 5.1000,
        -0.5450, 1.2650, 5.1000,
        -0.4450, 1.2450, 5.1000,
        -0.3100, 1.2200, 5.1000,
        -0.2850, 1.1200, 5.1000,
        -0.2800, 1.0150, 5.1000,
        -0.2750, 0.9400, 5.1000,
        -0.3050, 0.9000, 5.1000,
        -0.3150, 0.8650, 5.1000,
};

vector<float> cntrlPtComodeCover
{
    -0.2000, 1.7500, 5.1000,
        -0.2850, 1.7000, 5.1000,
        -0.3450, 1.6200, 5.1000,
        -0.3850, 1.4950, 5.1000,
        -0.3900, 1.3800, 5.1000,
        -0.3950, 1.2800, 5.1000,
        -0.3600, 1.1850, 5.1000,
        -0.2900, 1.1450, 5.1000,
        -0.2050, 1.1150, 5.1000,
        -0.1350, 1.1000, 5.1000,
        -0.0600, 1.1000, 5.1000,
        0.0150, 1.1000, 5.1000,
};


vector<float> cntrlPointsCylinderBase
{
    -0.6050, 1.4900, 5.1000,
        -0.6100, 1.3950, 5.1000,
        -0.6100, 1.3050, 5.1000,
        -0.6150, 1.2050, 5.1000,
        -0.6250, 1.1000, 5.1000,
        -0.6250, 1.0250, 5.1000,
        -0.6200, 0.9200, 5.1000,
};

vector<float> cntrlPtRocketBase
{
    -0.3400, 1.3850, 5.1000,
        -0.5000, 1.2400, 5.1000,
        -0.6850, 1.0550, 5.1000,
        -0.7600, 0.9100, 5.1000,
        -0.7400, 0.7700, 5.1000,
        -0.5400, 0.7250, 5.1000,
        -0.3500, 0.7250, 5.1000,
        -0.2050, 0.7300, 5.1000,
        -0.0300, 0.7150, 5.1000,
        0.1050, 0.7150, 5.1000,
};

vector<float> cntrlPtRocketHead
{
    -0.0150, 1.9200, 5.1000,
        -0.1200, 1.7850, 5.1000,
        -0.2900, 1.6850, 5.1000,
        -0.4500, 1.6050, 5.1000,
        -0.6000, 1.4850, 5.1000,
        -0.3950, 1.4550, 5.1000,
        -0.2450, 1.4450, 5.1000,
        -0.0950, 1.4550, 5.1000,
        0.0200, 1.4350, 5.1000,
};

vector<float> cntrlPtRocketBody
{
    -0.2500, 2.0000, 5.1000,
        -0.3300, 1.9550, 5.1000,
        -0.3450, 1.8500, 5.1000,
        -0.3550, 1.6350, 5.1000,
        -0.3600, 1.4300, 5.1000,
        -0.2700, 1.3150, 5.1000,
        -0.2250, 1.2450, 5.1000,
        -0.2300, 1.1900, 5.1000,
        -0.2700, 1.1700, 5.1000,
        -0.3700, 1.1300, 5.1000,
        -0.3650, 0.9750, 5.1000,
        -0.3600, 0.8150, 5.1000,
        -0.3600, 0.6800, 5.1000,
        -0.3700, 0.5600, 5.1000,
        -0.3700, 0.4500, 5.1000,
        -0.2750, 0.4000, 5.1000,
        -0.1800, 0.3700, 5.1000,
};
vector <float> coordinates;
vector <float> normals;
vector <int> indices;
vector <float> vertices;
class point
{
public:
    point()
    {
        x = 0;
        y = 0;
    }
    int x;
    int y;
} clkpt[2];
int mouseButtonFlag = 0;
FILE* fp;
const double pi = 3.14159265389;
const int nt = 40;
const int ntheta = 20;
bool showControlPoints = true;
bool loadBezierCurvePoints = false;
bool showHollowBezier = false;
bool lineMode = false;

unsigned int bezierVAO;
unsigned int bezierCylinderVAO;
unsigned int bezierBasinVAO;
unsigned int bezierSeatVAO;
unsigned int bezierComodeBaseVAO;
unsigned int bezierComodeCoverVAO;
unsigned int bezierCylinderBaseVAO;
unsigned int bezierRocketBaseVAO;
unsigned int bezierRocketHeadVAO;
unsigned int bezierRocketBodyVAO;
/*------------*/
/*------------*/
// camera
Camera camera(glm::vec3(0.0f, 2.5f+5.0f, 40.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 0.0, eyeY = 1.0, eyeZ = 3.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);

// positions of the point lights

glm::vec3 pointLightPositions[] = {
    glm::vec3(13.5f,  12.15f,  13.65f), //13.5 , 12.15, 13.65
    glm::vec3(40.5f,  12.15f,  13.65f), //40.5, 12.15, 13.65
    glm::vec3(5.5f,  6.15f,   -8.35f), //5.5, 6.15, -8.35
    
};

PointLight pointlight1(

    pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z,  // position
        
    0.5f, 0.5f, 0.5f,     // ambient
    .50f, .50f, .50f,     // diffuse
    1.0f, 1.0f, 1.0f,     // specular
    1.0f,   //k_c
    0.014f,  //k_l
    0.0007, //k_q
    1       // light number
);

PointLight pointlight3(

    pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z,  // position
    0.5f, 0.5f, 0.5f,     // ambient
    0.50f, .50f, .50f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.35f,  //k_l
    0.44f, //k_q
    2       // light number
);

PointLight pointlight4(

    pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z,  // position
    0.5f, 0.5f, 0.5f,     // ambient
    0.50f, .50f, .50f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.35f,  //k_l
    0.44f, //k_q
    3       // light number
);

DirLight dirLight(
        -0.2f, -1.0f, -0.3f,
        0.05f, 0.05f, 0.05f,
        .5f, 0.5f, 0.5f,     // diffuse
        0.5f, 0.5f, 0.5f
);

SpotLight spotLight(
    -3.50f, 4.0f, -2.0f, //pos
    0.6f, -1.0f, 0.5f, // dir
    0.5f, 0.0f, 0.5f, // ambient
    1.0f, 0.0f, 1.0f, //diffuse
    1.0f, 1.0f, 1.0f,  //specular
    1.0f, //kc
    0.09f, //kl
    0.032f, //kq
    12.5f, //cutoff
    15.0f //outer cutoff
);

// light settings
bool PointToggle1 = true;
bool PointToggle3 = true;
bool PointToggle4 = true;
bool ambientToggle = true;
bool diffuseToggle = true;
bool specularToggle = true;


// timing
float deltaTime = 1.5f;    // time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CSE 4208: Computer Graphics Laboratory", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    Shader lightingShader("vertexShaderForPhongShading.vs", "fragmentShaderForPhongShading.fs");
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    float cube_vertices[] = {
        // positions      // normals
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, //back side of cube, surface normal on -z 
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, //
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f
    };
    unsigned int cube_indices[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    unsigned int cubeVAO, cubeVBO, cubeEBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    /*-------------------*/
    bezierVAO = hollowBezier(cntrlPoints.data(), ((unsigned int)cntrlPoints.size() / 3) - 1);
    coordinates.clear();
    normals.clear();
    indices.clear();
    vertices.clear();

    bezierCylinderVAO = hollowBezier(cntrlPointsCylinder.data(), ((unsigned int)cntrlPointsCylinder.size() / 3) - 1);
    coordinates.clear();
    normals.clear();
    indices.clear();
    vertices.clear();

    bezierBasinVAO = hollowBezier(cntrlPointsBasin.data(), ((unsigned int)cntrlPointsBasin.size() / 3) - 1);
    coordinates.clear();
    normals.clear();
    indices.clear();
    vertices.clear();
    bezierSeatVAO = hollowBezier(cntrlPtSeat.data(), ((unsigned int)cntrlPtSeat.size() / 3) - 1);
    coordinates.clear();
    normals.clear();
    indices.clear();
    vertices.clear();
    bezierComodeBaseVAO = hollowBezier(cntrlPtComodeBase.data(), ((unsigned int)cntrlPtComodeBase.size() / 3) - 1);
    coordinates.clear();
    normals.clear();
    indices.clear();
    vertices.clear();
    bezierComodeCoverVAO = hollowBezier(cntrlPtComodeCover.data(), ((unsigned int)cntrlPtComodeCover.size() / 3) - 1);
    coordinates.clear();
    normals.clear();
    indices.clear();
    vertices.clear();

    bezierCylinderBaseVAO = hollowBezier(cntrlPointsCylinderBase.data(), ((unsigned int)cntrlPointsCylinderBase.size() / 3) - 1);
    coordinates.clear();
    normals.clear();
    indices.clear();
    vertices.clear();

    bezierRocketBaseVAO = hollowBezier(cntrlPtRocketBase.data(), ((unsigned int)cntrlPtRocketBase.size() / 3) - 1);
    coordinates.clear();
    normals.clear();
    indices.clear();
    vertices.clear();

    bezierRocketHeadVAO = hollowBezier(cntrlPtRocketHead.data(), ((unsigned int)cntrlPtRocketHead.size() / 3) - 1);
    coordinates.clear();
    normals.clear();
    indices.clear();
    vertices.clear();

    bezierRocketBodyVAO = hollowBezier(cntrlPtRocketBody.data(), ((unsigned int)cntrlPtRocketBody.size() / 3) - 1);



    /*------------------*/

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // render loop
    // -----------

    // abrar er vdo dekhe ana code
    Shader lightingShaderWithTexture("vertexShaderForPhongShadingWithTexture.vs", "fragmentShaderForPhongShadingWithTexture.fs");
    //Shader ourShader("vertexShader.vs", "fragmentShader.fs");
    string diffuseMapPath = "./container2.jpg";
    string specularMapPath = "./container2.jpg";
    string diffuseMapRoad = "./road.bmp";
    string specularMapRoad = "./road.bmp";
    string diffuseMapWater = "./water.bmp";
    string specularMapWater = "./water.bmp";
    string diffuseMapWood = "./wood.bmp";
    string specularMapWood = "./wood.bmp";
    string diffuseMapSeeSaw = "./seesawseat.bmp";
    string specularMapSeeSaw = "./seesawseat.bmp";
    string diffuseMapGrass = "./grass.bmp";
    string specularMapGrass = "./grass.bmp";
    string diffuseMapCement = "./cement.bmp";
    string specularMapCement = "./cement.bmp";
    string diffuseMapBrick = "./brick.bmp";
    string specularMapBrick = "./brick.bmp";
    string diffuseMapBench = "./bench.bmp";
    string specularMapBench = "./bench.bmp";
    string diffuseMapMetal = "./metalPole.bmp";
    string specularMapMetal = "./metalPole.bmp";
    string diffuseMapRope = "./rope.bmp";
    string specularMapRope = "./rope.bmp";
    string diffuseMapSky = "./skyback.bmp";
    string specularMapSky = "./skyback.bmp";
    string diffuseMapSkyl = "./skyleft.bmp";
    string specularMapSkyl = "./skyleft.bmp";
    string diffuseMapSkyr = "./skyright.bmp";
    string specularMapSkyr = "./skyright.bmp";
    string diffuseMapSeat = "./planeSeat.bmp";
    string specularMapSeat = "./planeSeat.bmp";
    string diffuseMapStick = "./planeStick.bmp";
    string specularMapStick = "./planeStick.bmp";
    string diffuseMapNestle = "./nestle.bmp";
    string specularMapNestle = "./nestle.bmp";
    string diffuseMapPartex1 = "./partex.bmp";
    string specularMapPartex1 = "./partex.bmp";
    string diffuseMapPartex2 = "./partex2.bmp";
    string specularMapPartex2 = "./partex2.bmp";
    string diffuseMapShatter = "./shatter.bmp";
    string specularMapShatter = "./shatter.bmp";
    string diffuseMapMirror = "./mirrors.bmp";
    string specularMapMirror = "./mirrors.bmp";
    string diffuseMapRailLine = "./railLine.bmp";
    string specularMapRailLine = "./railLine.bmp";
    string diffuseMapRedTrain = "./redtrain.bmp";
    string specularMapRedTrain = "./redtrain.bmp";
    string diffuseMapBlueTrain = "./bluetrain.bmp";
    string specularMapBlueTrain = "./bluetrain.bmp";
    string diffuseMapYellowTrain = "./yellowtrain.bmp";
    string specularMapYellowTrain = "./yellowtrain.bmp";
    string diffuseMapGreenTrain = "./greentrain.bmp";
    string specularMapGreenTrain = "./greentrain.bmp";
    string diffuseMapFood = "./food.bmp";
    string specularMapFood = "./food.bmp";
    string diffuseMapFreeze = "./freeze.bmp";
    string specularMapFreeze = "./freeze.bmp";
    string diffuseMapDrink = "./drink.bmp";
    string specularMapDrink = "./drink.bmp";
    string diffuseMapPattern = "./patterns.bmp";
    string specularMapPattern = "./patterns.bmp";

    unsigned int diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap1 = loadTexture(diffuseMapRoad.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap1 = loadTexture(specularMapRoad.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap2 = loadTexture(diffuseMapWater.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap2 = loadTexture(specularMapWater.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap3 = loadTexture(diffuseMapWood.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap3 = loadTexture(specularMapWood.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap4 = loadTexture(diffuseMapSeeSaw.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap4 = loadTexture(specularMapSeeSaw.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap5 = loadTexture(diffuseMapGrass.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap5 = loadTexture(specularMapGrass.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap6 = loadTexture(diffuseMapCement.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap6 = loadTexture(specularMapCement.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap7 = loadTexture(diffuseMapBrick.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap7 = loadTexture(specularMapBrick.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap8 = loadTexture(diffuseMapBench.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap8 = loadTexture(specularMapBench.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap9 = loadTexture(diffuseMapMetal.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap9 = loadTexture(specularMapMetal.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap10 = loadTexture(diffuseMapRope.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap10 = loadTexture(specularMapRope.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap11 = loadTexture(diffuseMapSky.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap11 = loadTexture(specularMapSky.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap12 = loadTexture(diffuseMapSeat.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap12 = loadTexture(specularMapSeat.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap13 = loadTexture(diffuseMapStick.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap13 = loadTexture(specularMapStick.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap14 = loadTexture(diffuseMapNestle.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap14 = loadTexture(specularMapNestle.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap15 = loadTexture(diffuseMapPartex1.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap15 = loadTexture(specularMapPartex1.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap16 = loadTexture(diffuseMapPartex2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap16 = loadTexture(specularMapPartex2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap17 = loadTexture(diffuseMapSkyl.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap17 = loadTexture(specularMapSkyl.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap18 = loadTexture(diffuseMapSkyr.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap18 = loadTexture(specularMapSkyr.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap19 = loadTexture(diffuseMapShatter.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap19 = loadTexture(specularMapShatter.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap20 = loadTexture(diffuseMapMirror.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap20 = loadTexture(specularMapMirror.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap21 = loadTexture(diffuseMapRailLine .c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap21 = loadTexture(specularMapRailLine.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap22 = loadTexture(diffuseMapRedTrain.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap22 = loadTexture(specularMapRedTrain.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap23 = loadTexture(diffuseMapBlueTrain.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap23 = loadTexture(specularMapBlueTrain.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap24 = loadTexture(diffuseMapYellowTrain.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap24 = loadTexture(specularMapYellowTrain.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap25 = loadTexture(diffuseMapGreenTrain.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap25 = loadTexture(specularMapGreenTrain.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap26 = loadTexture(diffuseMapFood.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap26 = loadTexture(specularMapFood.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap27 = loadTexture(diffuseMapFreeze.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap27 = loadTexture(specularMapFreeze.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap28 = loadTexture(diffuseMapDrink.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap28 = loadTexture(specularMapDrink.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int diffMap29 = loadTexture(diffuseMapPattern.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap29 = loadTexture(specularMapPattern.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    
    Cube road = Cube(diffMap1, specMap1, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube water = Cube(diffMap2, specMap2, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube wood = Cube(diffMap3, specMap3, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube seesaw = Cube(diffMap4, specMap4, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube grass = Cube(diffMap5, specMap5, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube cement = Cube(diffMap6, specMap6, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube brick = Cube(diffMap7, specMap7, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube bench = Cube(diffMap8, specMap8, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube metal = Cube(diffMap9, specMap9, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube rope = Cube(diffMap10, specMap10, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube sky = Cube(diffMap11, specMap11, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube seat = Cube(diffMap12, specMap12, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube stick = Cube(diffMap13, specMap13, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube nestle = Cube(diffMap14, specMap14, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube partex1 = Cube(diffMap15, specMap15, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube partex2 = Cube(diffMap16, specMap16, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube skyl = Cube(diffMap17, specMap17, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube skyr = Cube(diffMap18, specMap18, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube shatter = Cube(diffMap19, specMap19, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube mirror = Cube(diffMap20, specMap20, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube railLine = Cube(diffMap21, specMap21, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube redtrain = Cube(diffMap22, specMap22, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube bluetrain = Cube(diffMap23, specMap23, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube yellowtrain = Cube(diffMap24, specMap24, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube greentrain = Cube(diffMap25, specMap25, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube food = Cube(diffMap26, specMap26, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube freeze = Cube(diffMap27, specMap27, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube drink = Cube(diffMap28, specMap28, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube pattern = Cube(diffMap29, specMap29, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    //std::cout << diffMap << ' ' << specMap << std::endl;
    Cube cube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube cube1 = Cube();
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);
        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("viewPos", camera.Position);
        // point light 1
        pointlight1.setUpPointLight(lightingShader);
        // point light 3
        pointlight3.setUpPointLight(lightingShader);
        // point light 4
        pointlight4.setUpPointLight(lightingShader);
        dirLight.setUpDirLight(lightingShader);
        spotLight.setUpSpotLight(lightingShader);
        lightingShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        lightingShader.setMat4("projection", projection);
       
        /*-----------*/
        glm::mat4 identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(10., 3.750, -1.5));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(4, 2.5, 4));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.0f, 1.0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.0f, 1.0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierVAO);
        //glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        /*-----------------*/
        //draw a cylinder
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrixCurve, rotateXMatrixCurve, rotateYMatrixCurve, rotateZMatrixCurve, scaleMatrixCurve, modelforCurve;
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(15, 2, 20));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(3, 2.5, 3));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 0.0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        //glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw a cylilnder ends
        /*-----------------*/
       // //draw a basin
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(18.0f, -2.50f, -15.0f));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2, 3, 2));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierBasinVAO);
        glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
       //end basin
        /*--------------------------*/
        //draw a seat  
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(-3.70 + dx, 3.80, 0.70));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(1.5, 1.5, 1.5));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.0f, .40f, 0.80f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.0f, .40f, 0.80f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierSeatVAO);
        glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //end cable car seat
         /*------Ride2:Cable-Car--------*/
        //top
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(-3.70 + dx, 5.60, .70));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(1.3, 1, 1.3));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 1.0f, 0.50f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 1.0f, 0.50f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //stand
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(-3.70 + dx, 1.80, 0.70));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(0.10, 3.50, 0.10));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        if (flagR2 == 1)
        {
            dx = dx + 0.05;
            if (dx >= 33)
            {
                flagR2 = 2;
            }

        }
        if (flagR2 == 2)
        {
            dx = dx - 0.05;
            if (dx <= -0.5)
            {
                flagR2 = 5;
            }
        }

        /*----------------------*/
        //draw Comode Base
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(22.90f, -4.0f, -15.0f));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2, 3, 2));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f,1.f, 1.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierComodeBaseVAO);
        glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //end ComodeBase
        /*-----------------------------------*/
         //draw Comode Cover
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(23.0f, 6.20f, -16.0f));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(5.4, 3, 0.0));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 1.f, 1.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierComodeCoverVAO);
        glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //end Comode Cover
       /*------------------------------*/
        //draw Rocket Base
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(5.50f, -4.0f, 21.0f));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2, 3, 2));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .0f, 1.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .0f, 1.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierRocketBaseVAO);
        glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //end Rocket Base
        /*------------------------------*/
        //draw Rocket Body1
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(5.50f, -.60f, 21.0f));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2.5, 1.6, 2.5));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .50f, .50f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .50f, .50f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierRocketBodyVAO);
        glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw Rocket Body2
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(5.50f, 2.47f, 21.0f));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2.5, .4, 2.5));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .80f, .0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .80f, .0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierRocketBodyVAO);
        glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //draw Rocket Body3
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(5.50f, 2.60f, 21.0f));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2.5, 1.55, 2.5));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .50f, .50f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .50f, .50f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierRocketBodyVAO);
        glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //end Rocket Body
        /*----------------------------------*/
        //draw Rocket Head
        identityMatrixCurve = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(5.50f, 1.30f, 21.0f));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2, 3, 2));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * rotateYMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 0.f, 1.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.0f, 1.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierRocketHeadVAO);
        glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //end Rocket Head
        /*-----------------Ride_3--------------------*/
        //stand
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(5.750, -7.0, 5.60));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(.30, 6.0, .30));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        //top
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(5.750, 2.30, 5.60));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2.5, 1, 2.5));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        glBindVertexArray(bezierVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        //base
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(5.750, -0.850, 5.60));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(3.0, 0.1, 3.0));
        modelforCurve = translateMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        glBindVertexArray(bezierVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);


        //seat1
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(3.70 , .50 - d_up, 5.70));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(.7, .7, .7));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .80f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .80f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierSeatVAO);
        glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(3.70, -7.0, 5.70));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(.1, 6.0, .1));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        //seat2
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(4.30, -1.50 + d_up, 7.0));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(.7, .7, .7));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 0.40f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.40f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierSeatVAO);
        glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(4.30, -7.0, 7.0));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(.1, 6.0, .1));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //seat3
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(5.70, .50 - d_up, 7.70));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(.7, .7, .7));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .80f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .80f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierSeatVAO);
        glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(5.70, -7.0, 7.70));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(.1, 6.0, .1));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        //seat4
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(7.10, -1.50 + d_up, 7.0));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(.7, .7, .7));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 0.40f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.40f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierSeatVAO);
        glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(7.10, -7.0, 7.0));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(.1, 6.0, .1));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //seat5
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(7.70, 0.50 - d_up, 5.70));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(.7, .7, .7));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .80f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .80f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierSeatVAO);
        glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(7.70, -7.0, 5.70));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(.1, 6.0, .1));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //seat6
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(7.30, -1.50 + d_up, 4.10));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(.7, .7, .7));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 0.40f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.40f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierSeatVAO);
        glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(7.30, -7.0, 4.10));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(.1, 6.0, .1));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
       
        //seat7
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(5.70, 0.50 - d_up, 3.50));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(.7, .7, .7));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .80f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .80f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierSeatVAO);
        glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(5.70, -7.0, 3.50));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(.1, 6.0, .1));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);


        //seat8
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(4.30, -1.50 + d_up, 4.10));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(.7, .7, .7));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 0.4f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.4f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierSeatVAO);
        glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(4.30, -7.0, 4.10));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(.1, 6.0, .1));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        if (flag3 == 1)
        {
            d_up = d_up + 0.1;
            if (d_up >= 2)
            {
                flag3 = 2;
            }

        }
        if (flag3 == 2)
        {
            d_up = d_up - 0.1;
            if (d_up <= -0.05)
            {
                flag3 = 3;
            }

        }
        if (flag3 == 3)
        {
            d_up = d_up + 0.1;
            if (d_up >= 2)
            {
                flag3 = 4;
            }

        }
        if (flag3 == 4)
        {
            d_up = d_up - 0.1;
            if (d_up <= -0.05)
            {
                flag3 = 33;
            }

        }

        /*------------extra(RIDE_4)------------*/
        //stand
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(18.80, -16.0, 20.60));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(.30, 14.0, .30));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

          //seat1
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(20.70, 2.70 + dy4, 20.70)); //2.70
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(1.0, .7, 1.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(0.0f + drx), glm::vec3(1.0f, 0.0f, 0.0f));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .50f, .50f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .50f, .50f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierSeatVAO);
        glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(18.70, 3.10 + dy4, 20.70));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(6.0, .10, .1));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //seat2
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(17.0, 2.70 + dy4, 20.70));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(1.0, .7, 1.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(0.0f + drx), glm::vec3(1.0f, 0.0f, 0.0f));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .50f, .50));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .50f, .50));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierSeatVAO);
        glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //seat3
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(18.85, 2.70 + dy4, 18.70));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(1.0, .7, 1.0));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(0.0f + drx), glm::vec3(0.0f, 0.0f, 1.0f));
        modelforCurve = translateMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .50f, .50));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .50f, .50));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierSeatVAO);
        glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);


        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(18.80, 3.10 + dy4, 20.70));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(.10, .10, 6.0));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //seat4
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(18.85, 2.70 + dy4, 22.70));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(1.0, .7, 1.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(0.0f + drx), glm::vec3(.0f, 0.0f, 1.0f));
        modelforCurve = translateMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .50f, .50f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .50f, .50f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierSeatVAO);
        glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        //seat5
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(20.70, .80 + dy4, 20.70)); //0.7
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(1.0, .7, 1.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(0.0f + drx), glm::vec3(1.0f, 0.0f, .0f));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.40f, .0f, 0.40f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.40f, .0f, 0.40f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierSeatVAO);
        glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(18.70, 1.20 + dy4, 20.70));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(6.0, .10, .1));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);


        //seat6
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(17.0, .80 + dy4, 20.70));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(1.0, .7, 1.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(0.0f + drx), glm::vec3(1.0f, 0.0f, 0.0f));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.40f, .0f, 0.40f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.40f, .0f, 0.40f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierSeatVAO);
        glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //seat7
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(18.85, .80 + dy4, 18.70));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(1.0, .7, 1.0));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(0.0f + drx), glm::vec3(0.0f, 0.0f, 1.0f));
        modelforCurve = translateMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.40f, .0f, 0.40f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.40f, .0f, 0.40f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierSeatVAO);
        glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(18.80, 1.20 + dy4, 20.70));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(.10, .10, 6.0));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //seat8
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(18.85, .80 + dy4, 22.70));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(1.0, .7, 1.0));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(0.0f + drx), glm::vec3(0.0f, 0.0f, 1.0f));
        modelforCurve = translateMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.40f, .0f, 0.40f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.40f, .0f, 0.40f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierSeatVAO);
        glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);


        //seat9
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(20.70, 4.60 + dy4, 20.70)); //2.70
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(1.0, .7, 1.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(0.0f + drx), glm::vec3(1.0f, 0.0f, 0.0f));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.40f, .0f, 0.40f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.40f, .0f, 0.40f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierSeatVAO);
        glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(18.70, 5.0 + dy4, 20.70));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(6.0, .10, .1));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //seat10
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(17.0, 4.60 + dy4, 20.70));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(1.0, .7, 1.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(0.0f + drx), glm::vec3(1.0f, 0.0f, 0.0f));
        modelforCurve = translateMatrixCurve * rotateXMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.40f, .0f, 0.40f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.40f, .0f, 0.40f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierSeatVAO);
        glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //seat11
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(18.85, 4.60 + dy4, 18.70));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(1.0, .7, 1.0));
        rotateZMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(0.0f + drx), glm::vec3(0.0f, 0.0f, 1.0f));
        modelforCurve = translateMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.40f, .0f, 0.40f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.40f, .0f, 0.40f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierSeatVAO);
        glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(18.80, 5.0 + dy4, 20.70));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(.10, .10, 6.0));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //seat12
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(18.85, 4.60 + dy4, 22.70));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(1.0, .7, 1.0));
        rotateXMatrixCurve = glm::rotate(identityMatrixCurve, glm::radians(0.0f + drx), glm::vec3(.0f, 0.0f, 1.0f));
        modelforCurve = translateMatrixCurve * rotateZMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.40f, .0f, 0.40f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.40f, .0f, 0.40f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierSeatVAO);
        glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);


        // rotation1
        if (flag_ex == 1)
        {
            drx = drx + 0.35;
            if (drx >= 30)
            {
                flag_ex = 2;
            }

        }
        if (flag_ex == 2)
        {
            drx = drx - 0.35;
            if (drx <= -30)
            {
                flag_ex = 3;
            }
        }
        if (flag_ex == 3)
        {
            drx = drx + 0.35;
            if (drx >= 0)
            {
                flag_ex = 4;
            }
        }
        //up down
        if (flag_ex == 4)
        {
            dy4 = dy4 + 0.15;
            if (dy4 >= 3)
            {
                flag_ex = 5;
            }

        }
        if (flag_ex == 5)
        {
            dy4 = dy4 - 0.15;
            if (dy4 <= -1)
            {
                flag_ex = 6;
            }
        }
        if (flag_ex == 6)
        {
            dy4 = dy4 + 0.15;
            if (dy4 >= 3)
            {
                flag_ex = 7;
            }

        }
       
        //rotation2
        if (flag_ex == 7)
        {
            drx = drx + 0.35;
            if (drx >= 30)
            {
                flag_ex = 8;
            }

        }
        if (flag_ex == 8)
        {
            drx = drx - 0.35;
            if (drx <= -30)
            {
                flag_ex = 9;
            }
        }
        if (flag_ex == 9)
        {
            drx = drx + 0.35;
            if (drx >= 0)
            {
                flag_ex = 10;
            }
        }
        //up down
        if (flag_ex == 10)
        {
            dy4 = dy4 - 0.15;
            if (dy4 <= -1)
            {
                flag_ex = 11;
            }
        }
        /*---tree----*/
        //tree1
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(-15.0, -10.0, -1.50));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(1.0, 9.0, 1.0));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(-15.0, -6.8, -1.5));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2, 10, 2));
        modelforCurve = translateMatrixCurve  * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.0f, 1.0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.0f, 1.0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);


        //tree2
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(-15.0, -10.10, 5.50));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(0.8, 9.0, 0.8));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(-15.0, -6.8, 5.5));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2, 10, 2));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.0f, 1.0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.0f, 1.0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);

        //tree3
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(-15.0, -10.10, 11.50));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(0.8, 9.0, 0.8));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve); lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(-15.0, -6.8, 11.5));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2, 10, 2));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve); lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.0f, 1.0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.0f, 1.0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);

        //tree4
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(-15.0, -10.10, 17.50));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(0.8, 9.0, 0.8));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve); lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(-15.0, -6.8, 17.5));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2, 10, 2));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve); lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.0f, 1.0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.0f, 1.0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);

        //tree5
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(-15.0, -10.10, 23.50));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(0.8, 9.0, 0.8));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve); lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(-15.0, -6.8, 23.5));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2, 10, 2));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve); lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.0f, 1.0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.0f, 1.0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);


        //tree6
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(42.50, -10.10, -13.50));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(0.8, 9.0, 0.8));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve); 
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(42.50, -6.8, -13.5));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2, 10, 2));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve); 
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.0f, 1.0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.0f, 1.0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);

        //tree7
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(42.50, -10.10, -7.50));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(0.8, 9.0, 0.8));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve); lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(42.50, -6.8, -7.5));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2, 10, 2));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.0f, 1.0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.0f, 1.0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        lightingShader.setMat4("model", modelforCurve);
        glBindVertexArray(bezierVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);

        //tree8
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(42.50, -10.10, -1.50));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(0.8, 9.0, 0.8));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve); lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(42.50, -6.8, -1.5));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2, 10, 2));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.0f, 1.0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.0f, 1.0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);

        //tree9
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(42.50, -10.10, 5.50));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(0.8, 9.0, 0.8));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve); lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(42.50, -6.8, 5.5));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2, 10, 2));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.0f, 1.0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.0f, 1.0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);

        //tree10
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(42.50, -10.10, 11.50));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(0.8, 9.0, 0.8));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve); lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(42.50, -6.8, 11.5));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2, 10, 2));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.0f, 1.0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.0f, 1.0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);

        //tree11
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(42.50, -10.10, 17.50));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(0.8, 9.0, 0.8));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve); lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(42.50, -6.8, 17.5));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2, 10, 2));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.0f, 1.0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.0f, 1.0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);

        //tree12
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(42.50, -10.10, 23.50));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(0.8, 9.0, 0.8));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve); lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, .0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        translateMatrixCurve = glm::translate(identityMatrixCurve, glm::vec3(42.50, -6.8, 23.5));
        scaleMatrixCurve = glm::scale(identityMatrixCurve, glm::vec3(2, 10, 2));
        modelforCurve = translateMatrixCurve * scaleMatrixCurve;
        lightingShader.setMat4("model", modelforCurve);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(0.0f, 1.0f, 0.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(0.0f, 1.0f, 0.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 50.0f);
        glBindVertexArray(bezierVAO);
        glDrawElements(GL_TRIANGLE_FAN, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);



        // camera/view transformation
        float degree = 0;
        glm::mat4 view = camera.GetViewMatrix();
        float r = glm::length(camera.Position - glm::vec3(view[3]));
        ourShader.setMat4("view", view);

        // Modelling Transformation
        /*------------------------------INSIDE GROUND----------------------------*/
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix26, rotateXMatrix26, rotateYMatrix26, rotateZMatrix26, scaleMatrix26, model26;
        translateMatrix26 = glm::translate(identityMatrix, glm::vec3(-2, -1.1, -2.0));
        rotateXMatrix26 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix26 = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix26 = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix26 = glm::scale(identityMatrix, glm::vec3(30.0, 30.0, 1.0));
        model26 = translateMatrix26 * rotateXMatrix26 * rotateYMatrix26 * rotateZMatrix26 * scaleMatrix26;
        lightingShader.setMat4("model", model26);
        grass.drawCubeWithTexture(lightingShaderWithTexture, model26);

        /*--------------------------INSIDE FENCHING------------------------*/
        //left side(1-10)
        glm::mat4 translateMatrix_b1, rotateXMatrix_b1, rotateYMatrix_b1, rotateZMatrix_b1, scaleMatrix_b1, model_b1;
            // stand1
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-1.50, -1.10, -1.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
       
            //stand2
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-1.50, -1.10, 2.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand3
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-1.50, -1.10, 5.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
       
            //stand4
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-1.50, -1.10,8.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand5
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-1.50, -1.10, 11.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand6
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-1.50, -1.10, 15.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;

            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand7
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-1.50, -1.10, 18.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand8
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-1.50, -1.10, 21.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand9
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-1.50, -1.10, 24.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand10
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-1.50, -1.10, 27.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        // Right side(11-20)
            //stand11
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(27.50, -1.10, -1.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand12
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(27.50, -1.10, 2.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand13
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(27.50, -1.10, 5.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand14
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(27.50, -1.10, 8.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
        
            //stand15
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(27.50, -1.10, 11.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand16
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(27.50, -1.10, 15.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;

            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand17
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(27.50, -1.10, 18.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand18
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(27.50, -1.10, 21.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand19
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(27.50, -1.10, 24.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            road.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand20
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(27.50, -1.10, 27.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //North side(21-28)
              // stand21
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(2.50, -1.10, -1.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand22
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(5.50, -1.10, -1.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand23
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(8.50, -1.10, -1.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand24
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(11.50, -1.10, -1.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            road.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand25
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(15.50, -1.10, -1.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand26
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(18.50, -1.10, -1.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand27
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(21.50, -1.10, -1.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand28
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(24.50, -1.10, -1.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //chain1(north)
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-1.50, 0.00, -1.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(29.0f, 0.15f, 0.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            rope.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-1.50, -0.60, -1.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(29.0f, 0.15f, 0.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            rope.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-1.50, 0.50, -1.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(29.0f, 0.15f, 0.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            rope.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //chain1(left)
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-1.50, 0.00, -1.50));//middle
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 13.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            rope.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-1.50, -0.60, -1.50));//down
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 13.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            rope.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-1.50, 0.50, -1.50));//up
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 13.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            rope.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //chain2(left)
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-1.50, 0.00, 15.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 12.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            rope.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-1.50, -0.60, 15.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 12.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            rope.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-1.50, 0.50, 15.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 12.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            rope.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //chain1(right)
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(27.50, 0.00, -1.50)); //27.50, -1.10, -1.50
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 13.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            rope.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(27.50, -0.60, -1.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 13.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            rope.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(27.50, 0.50, -1.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 13.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            rope.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //chain2(right)
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(27.50, 0.00, 15.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 12.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            rope.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(27.50, -0.60, 15.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 12.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            rope.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(27.50, 0.50, 15.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 12.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            rope.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
   
           /*-------------------------- OUTSIDE FENCHING --------------------------------*/
             //left side(1-10)
            // stand1
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-6.50, -1.10, -1.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand2
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-6.50, -1.10, 2.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand3
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-6.50, -1.10, 5.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand4
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-6.50, -1.10, 8.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand5
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-6.50, -1.10, 11.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand6
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-6.50, -1.10, 15.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;

            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand7
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-6.50, -1.10, 18.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand8
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-6.50, -1.10, 21.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand9
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-6.50, -1.10, 24.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand10
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-6.50, -1.10, 27.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //chain1(left)
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-6.50, 0.00, -6.50));//middle
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 18.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            rope.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-6.50, -0.60, -6.50));//down
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 18.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            rope.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-6.50, 0.50, -6.50));//up
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 18.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            rope.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //chain2(left)
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-6.50, 0.00, 15.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 12.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            rope.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-6.50, -0.60, 15.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 12.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            rope.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-6.50, 0.50, 15.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 12.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            rope.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            // Right side(11-20)
           //stand11
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(33.0, -1.10, -1.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand12
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(33.0, -1.10, 2.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand13
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(33.0, -1.10, 5.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand14
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(33.0, -1.10, 8.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand15
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(33.0, -1.10, 11.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand16
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(33.0, -1.10, 15.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand17
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(33.0, -1.10, 18.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand18
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(33.0, -1.10, 21.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand19
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(33.0, -1.10, 24.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            road.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand20
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(33.0, -1.10, 27.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //chain1(right)
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(33.0, 0.00, -6.50)); //27.50, -1.10, -1.50
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 18.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            rope.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(33.0, -0.60, -6.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 18.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            rope.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(33.0, 0.50, -6.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 18.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            rope.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //chain2(right)
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(33.0, 0.00, 15.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 12.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            rope.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(33.0, -0.60, 15.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 12.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            rope.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(33.0, 0.50, 15.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.0f, 0.15f, 12.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            rope.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //North side(21-28)
            // ****
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-6.50, -1.10, -6.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            // ****
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-2.50, -1.10, -6.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

             // stand21
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(2.50, -1.10, -6.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand22
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(5.50, -1.10, -6.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand23
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(8.50, -1.10, -6.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand24
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(11.50, -1.10, -6.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand25
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(15.50, -1.10, -6.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand26
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(18.50, -1.10, -6.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand27
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(21.50, -1.10, -6.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            road.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand28
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(24.50, -1.10, -6.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
            //***
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(28.50, -1.10, -6.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
            //***
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(33.0, -1.10, -6.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //chain1(north)
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-6.50, 0.0, -6.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(39.50f, 0.15f, 0.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            rope.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-6.50, -0.60, -6.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(39.50f, 0.15f, 0.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            rope.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-6.50, 0.50, -6.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(39.50f, 0.15f, 0.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            rope.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
   
        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);
        glm::mat4 modelCircle = glm::mat4(1.0f);
 

        // we now draw as many light bulbs as we have point lights.

        glBindVertexArray(lightCubeVAO);
       /* ourShader.use();
        for (unsigned int i = 0; i < 2; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(2.0f, 2.0f, 0.9f)); // Make it a smaller cube
            ourShader.setMat4("model", model);
            ourShader.setVec3("color", glm::vec3(1.0f, 1.0f, 1.0f));

            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }*/

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        lightingShaderWithTexture.use();
        lightingShaderWithTexture.setVec3("viewPos", camera.Position);
        lightingShaderWithTexture.setMat4("projection", projection);
        lightingShaderWithTexture.setMat4("view", view);
        //2nd part of cube draw
        lightingShaderWithTexture.use();
        // point light 1
        pointlight1.setUpPointLight(lightingShaderWithTexture);
        // point light 3
        pointlight3.setUpPointLight(lightingShaderWithTexture);
        // point light 4
        pointlight4.setUpPointLight(lightingShaderWithTexture);

        // surface
        //glm::mat4 modelMatrixForContainer = glm::mat4(1.0f);
        //translateMatrix26 = glm::translate(identityMatrix, glm::vec3(-2, -1.1, -2.0));
        //scaleMatrix26 = glm::scale(identityMatrix, glm::vec3(30.0, 30.0, .2));
        //modelMatrixForContainer = translateMatrix26 * scaleMatrix26;
        ////modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.45f, -0.4f, -2.8f));
        //cube.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        /*------------------------------road-------------------------*/
       //road1 (x-axis)
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-2.0f, -1.08f, 11.50f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(30.0f, 0.0f, 4.0f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        road.drawCubeWithTexture(lightingShaderWithTexture, model_b1);


        //road2(z-axis)
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(10.50f, -1.09f, -2.0f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(3.0f, 0.0f, 30.0f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        road.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        /*--------------------------------POND-----------------------------*/
       //left
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-6.0f, -2.0f, -2.0f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(4.0f, 0.0f, 30.0f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        water.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-5.950f, -2.0f, -6.0f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.0f, 1.0f, 34.0f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        cement.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-2.05f, -2.0f, -2.0f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.0f, 1.0f, 30.0f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        cement.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //up
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-6.0f, -2.0f, -6.0f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(38.0f, 0.0f, 4.0f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        water.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-6.0f, -2.0f, -5.950f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(38.0f, 1.0f, 0.0f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        cement.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-2.1f, -2.0f, -2.0f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(30.0f, 1.0f, 0.0f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        cement.drawCubeWithTexture(lightingShaderWithTexture, model_b1);


        //right
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(28.0f, -2.0f, -2.0f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(4.0f, 0.0f, 30.0f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        water.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(28.05f, -2.0f, -2.0f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.0f, 1.0f, 30.0f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        cement.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(31.95f, -2.0f, -6.0f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.0f, 1.0f, 34.0f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        cement.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        /*--------------------------------OUTSIDE GROUND-----------------------------*/
        //left
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-18.0f, -1.09f, -6.0f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(12.0f, -1.0f, 34.0f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        grass.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //up
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-18.0f, -1.1f, -18.0f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(63.0f, -1.0f, 12.0f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        grass.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //right
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(32.0f, -1.09f, -6.0f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(13.0f, -1.0f, 34.0f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        grass.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        /*----------------------------sky----------------------------------*/
        ////back
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-18.0f, -1.1f, -18.0f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(63.0f, 30.0f, 0.0f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        sky.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
        ////left
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-18.0f, -1.1f, -18.0f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.0f, 30.0f, 46.0f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        skyl.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
        ////right
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(45.0f, -1.1f, -18.0f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.0f, 30.0f, 46.0f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        skyr.drawCubeWithTexture(lightingShaderWithTexture, model_b1);


        /*------------------------------seesaw-----------------------------------*/
       //Seesaw1 base right
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(1.750, -0.50, 25.5));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(2.0f, .05f, 1.20f));
        rotateZMatrix_b1 = glm::rotate(identityMatrix, glm::radians(0.0f + dr), glm::vec3(0.0f, 0.0f, 1.0f));
        model_b1 = translateMatrix_b1 * rotateZMatrix_b1 * scaleMatrix_b1;
        partex2.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
        //Seesaw1 base left
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(1.750, -0.50, 25.5));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-2.0f, .05f, 1.20f));
        rotateZMatrix_b1 = glm::rotate(identityMatrix, glm::radians(0.0f +dr), glm::vec3(0.0f, 0.0f, 1.0f));
        model_b1 = translateMatrix_b1 * rotateZMatrix_b1  *scaleMatrix_b1;
        partex2.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //base movement
        if (flag_ss == 1)
        {
            dr = dr + 0.5;
            if (dr >= 15)
            {
                flag_ss = 2;
            }

        }
        if (flag_ss == 2)
        {
            dr = dr - 0.5;
            if (dr <= -15)
            {
                flag_ss = 3;
            }
        }
        if (flag_ss == 3)
        {
            dr = dr + 0.5;
            if (dr >= 15)
            {
                flag_ss = 4;
            }

        }
        if (flag_ss == 4)
        {
            dr = dr - 0.5;
            if (dr <= -15)
            {
                flag_ss = 5;
            }
        }
        
        //seesaw1 base pillar back
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(1.750, -1.10, 25.40));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.25f, 0.80f, 0.05f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        brick.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //seesaw1 base pillar front
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(1.750, -1.10, 26.70));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.25f, 0.80f, 0.05f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        brick.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        /*------------------------RIDE_3-------------------------*/
      /*  translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(6.0, -1.10, 18.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
      */

        /*--------------------------RIDE_5----------------------------*/
         
            //stand1
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(19.0, -1.10, 25.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 4.30f, .20f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            pattern.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
            //stand2
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(21.0, -1.10, 25.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 6.0f, .20f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            pattern.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
            //stand3
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(24.0, -1.10, 25.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 6.0f, .20f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            pattern.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //stand4
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(26.0, -1.10, 25.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 4.30f, .20f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            pattern.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //beam
        //1
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(19.0, 0.0, 25.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(2.0f, 0.20f, .10f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        pattern.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(24.0, 0.0, 25.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(2.0f, 0.20f, .10f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        pattern.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //2
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(19.0, 1.0, 25.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(2.0f, 0.20f, .10f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        pattern.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(24.0, 1.0, 25.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(2.0f, 0.20f, .10f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        pattern.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

       //3
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(19.0, 2.0, 25.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(2.0f, 0.20f, .10f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        pattern.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(24.0, 2.0, 25.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(2.0f, 0.20f, .10f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        pattern.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

       //4
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(19.0, 3.0, 25.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(2.0f, 0.20f, .10f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        pattern.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(24.0, 3.0, 25.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(2.0f, 0.20f, .10f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        pattern.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //up
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(20.80, 4.80, 25.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(3.250f, 0.20f, .10f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        pattern.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //handle1
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(21.90, 4.80, 25.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.1f, -1.50f, .10f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        pattern.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //handle2
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(22.90, 4.80, 25.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.1f, -1.50f, .10f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        pattern.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        /*-------------------------RIDE_2(Cable Car)  ------------------------*/
        //stand1
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-5.60, -2.0, 1.0));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 11.0f, -0.4f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //stand2
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(30.0, -2.0, 1.0));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 11.0f, -0.4f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //rope
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-5.60, 8.0, 1.0));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(35.50f, 0.15f, -0.15f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //basement
         // stand1
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-2.30, -2.0, -1.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 9.50f, 0.05f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //stand2
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-2.30, -2.0, 2.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 9.50f, 0.05f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        // stand3
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-5.30, -2.0, -1.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 9.50f, 0.05f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //stand4
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-5.30, -2.0, 2.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 9.50f, 0.05f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
        //box
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-2.30, 5.0, -1.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-3.20f, -.50f, 4.20f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //back 3 chains
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-2.30, 7.30, -1.60));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-3.20f, 0.10f, .10f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-2.30, 6.30, -1.60));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-3.20f, 0.10f, .10f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-2.30, 5.30, -1.60));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-3.20f, 0.10f, .10f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //front 3 chains
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-2.30, 7.30, 2.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-3.20f, 0.10f, .10f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-2.30, 6.30, 2.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-3.20f, 0.10f, .10f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-2.30, 5.30, 2.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-3.20f, 0.10f, .10f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //left 3 chains
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-5.30, 7.30, 2.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.10f, 0.10f, -4.10f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-5.30, 6.30, 2.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.10f, 0.10f, -4.10f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-5.30, 5.30, 2.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.10f, 0.10f, -4.10f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
        
        //stairs
        //back-down
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-2.30, 5.0, -1.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(7.0f, -.40f, .10f));
        rotateYMatrix_b1 = glm::rotate(identityMatrix, glm::radians(-60.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model_b1 = translateMatrix_b1 * rotateYMatrix_b1 * scaleMatrix_b1;
        partex2.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
        //back-up
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-2.40, 7.30, -1.51));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(7.30f, 0.10f, .10f));
        rotateYMatrix_b1 = glm::rotate(identityMatrix, glm::radians(-60.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model_b1 = translateMatrix_b1 * rotateYMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
        //1
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(.45, -0.60, -1.5));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.50f, -.10f, 4.0f));
        rotateYMatrix_b1 = glm::rotate(identityMatrix, glm::radians(2.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model_b1 = translateMatrix_b1 * rotateYMatrix_b1 * scaleMatrix_b1;
        partex2.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //2
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-0.1, 0.40, -1.5));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.50f, -.10f, 4.0f));
        rotateYMatrix_b1 = glm::rotate(identityMatrix, glm::radians(2.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model_b1 = translateMatrix_b1 * rotateYMatrix_b1 * scaleMatrix_b1;
        partex2.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //3
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-0.55, 1.2, -1.5));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.50f, -.10f, 4.0f));
        rotateYMatrix_b1 = glm::rotate(identityMatrix, glm::radians(2.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model_b1 = translateMatrix_b1 * rotateYMatrix_b1 * scaleMatrix_b1;
        partex2.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //4
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-1.0, 2.0, -1.5));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.50f, -.10f, 4.0f));
        rotateYMatrix_b1 = glm::rotate(identityMatrix, glm::radians(2.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model_b1 = translateMatrix_b1 * rotateYMatrix_b1 * scaleMatrix_b1;
        partex2.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //5
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-1.5, 2.8, -1.5));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.50f, -.10f, 4.0f));
        rotateYMatrix_b1 = glm::rotate(identityMatrix, glm::radians(2.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model_b1 = translateMatrix_b1 * rotateYMatrix_b1 * scaleMatrix_b1;
        partex2.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //6
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-2.0, 3.6, -1.5));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.50f, -.10f, 4.0f));
        rotateYMatrix_b1 = glm::rotate(identityMatrix, glm::radians(2.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model_b1 = translateMatrix_b1 * rotateYMatrix_b1 * scaleMatrix_b1;
        partex2.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //7
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-2.4, 4.3, -1.5));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.50f, -.10f, 4.0f));
        rotateYMatrix_b1 = glm::rotate(identityMatrix, glm::radians(2.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model_b1 = translateMatrix_b1 * rotateYMatrix_b1 * scaleMatrix_b1;
        partex2.drawCubeWithTexture(lightingShaderWithTexture, model_b1);


        //pillars
        /*-1-*/
         //1
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(1.20, -1.10, -1.5));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.10f, 2.30f, .10f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //2
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(1.20, -1.10, 2.5));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.10f, 2.30f, .10f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //front-down
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-2.30, 5.0, 2.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(7.0f, -.40f, .10f));
        rotateYMatrix_b1 = glm::rotate(identityMatrix, glm::radians(-60.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model_b1 = translateMatrix_b1 * rotateYMatrix_b1 * scaleMatrix_b1;
        partex2.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
        //front-up
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-2.40, 7.30, 2.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(7.30f, 0.10f, .10f));
        rotateYMatrix_b1 = glm::rotate(identityMatrix, glm::radians(-60.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model_b1 = translateMatrix_b1 * rotateYMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);



        /*------------------------RIDE_1(Up-Down)---------------------*/
        //stand1
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(26.0, -1.10, 5.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.20f, 15.0f, 0.05f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //stand2
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(26.0, -1.10, 7.0));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.20f, 15.0f, 0.05f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
        //base
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(23.00, -1.1, 3.0));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(3.50f, 0.80f, 6.50f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        cement.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //upper beam
        //1
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(26.0, 0.0, 5.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.20f, 0.20f, 1.5f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //2
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(26.0, 1.0, 5.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.20f, 0.20f, 1.5f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //3
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(26.0, 2.0, 5.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.20f, 0.20f, 1.5f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //4
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(26.0, 3.0, 5.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.20f, 0.20f, 1.5f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //5
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(26.0, 4.0, 5.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.20f, 0.20f, 1.5f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //6
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(26.0, 5.0, 5.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.20f, 0.20f, 1.5f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //7
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(26.0, 6.0, 5.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.20f, 0.20f, 1.5f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //8
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(26.0, 7.0, 5.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.20f, 0.20f, 1.5f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //9
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(26.0, 8.0, 5.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.20f, 0.20f, 1.5f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //10
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(26.0, 9.0, 5.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.20f, 0.20f, 1.5f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //11
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(26.0, 10.0, 5.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.20f, 0.20f, 1.5f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //12
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(26.0, 11.0, 5.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.20f, 0.20f, 1.5f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //13
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(26.0, 12.0, 5.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.20f, 0.20f, 1.5f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //14
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(26.0, 13.0, 5.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.20f, 0.20f, 1.5f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        // seat
          // base
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(24.00, 0.0+dy, 3.0));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(2.0f, 0.20f, 6.50f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        seat.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //seat uporer part
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(25.80f, 0.0f+dy, 3.00f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.20f, 2.10f, 6.50f));
        //scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.20f, 2.10f, 5.0f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        seat.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
          
        //handle left
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(25.80, 1.0+dy, 3.0));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-1.80f, .10f, 0.10f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);


        ////handle right
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(25.80, 1.0+dy, 9.40));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-1.80f, .10f, .10f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //handle front
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(24.0, 1.0+dy, 3.0));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.10f, 0.10f, 6.50f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //dy = dy + 0.005;
        if (flag == 1)
        {
            dy = dy + 0.05;
            if (dy >= 12)
            {
                flag = 2;
            }
        }
        if (flag == 2)
        {
            dy = dy - 0.1;
            if (dy <= 0)
            {
                flag = 4;
            }
        }

        /*----------------------------swing----------------------------*/
       //stand1
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(14.50, -1.10,9.0));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
     
        //stand2
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(17.50, -1.10, 9.0));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
      
        //stand3
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(20.50, -1.10, 9.0));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 3.0f, 0.05f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
       
        //upper beam
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(14.0, 1.30, 9.10));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(7.0f, 0.20f, -0.15f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        stick.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
       
        //Swing1
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(14.90, -0.50, 9.250 +dz));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(2.0f, .15f, -0.5f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        partex2.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
     
        //swing1 leg1
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(15.05, -0.50, 9.0+dz));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.05f, 1.9f, 0.05f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //Swing1 leg2
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(16.80, -0.50, 9.0+dz));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.05f, 1.9f, 0.05f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //Swing2
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(17.90, -0.50, 8.80+dz));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(2.0f, .15f, 0.5f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        partex2.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //swing2 leg1
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(18.05, -0.50, 9.0+dz));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.05f, 1.9f, 0.05f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
       
        //Swing2 leg2
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(19.80, -0.50, 9.0+dz));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.05f, 1.9f, 0.05f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        rope.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

          //dy = dy + 0.005;
                if (swingFlag == 1)
                {
                        dz = dz + 0.2;
                        if (dz >= 0.5)
                        {
                            swingFlag = 2;
                        }
                    
                }
                if (swingFlag == 2)
                {
                    dz = dz - 0.2;
                    if (dz <= -0.5)
                    {
                        swingFlag = 3;
                    }
                }
                if (swingFlag == 3)
                {
                    dz = dz + 0.2;
                    if (dz >= 0.5)
                    {
                        swingFlag = 4;
                    }

                }
                if (swingFlag == 4)
                {
                    dz = dz - 0.2;
                    if (dz <= -0.5)
                    {
                        swingFlag = 5;
                    }
                }
                if (swingFlag == 5)
                {
                    dz = dz + 0.2;
                    if (dz >= 0.5)
                    {
                        swingFlag = 6;
                    }

                }
                if (swingFlag == 6)
                {
                    dz = dz - 0.2;
                    if (dz <= -0.5)
                    {
                        swingFlag = 7;
                    }
                }
        /*------------------------slipper------------------------*/

        // back stand rallying
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(14.00, -1.10, .50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 5.90f, 0.05f));
        rotateYMatrix_b1 = glm::rotate(identityMatrix, glm::radians(-25.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model_b1 = translateMatrix_b1 * rotateYMatrix_b1 * scaleMatrix_b1 ;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        // back stand (/)
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(15.00, -1.10, .50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 4.10f, 0.05f));
        rotateYMatrix_b1 = glm::rotate(identityMatrix, glm::radians(-20.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model_b1 = translateMatrix_b1 * rotateYMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
        
        // back left stand (|)
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(16.50, -1.10, .50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 5.40f, 0.05f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        // back upper beam (---)
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(16.30, 4.10, .50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(2.50f, .20f, 0.05f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

       
        // back right stand (|)
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(18.80, -1.10, .50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 5.40f, 0.05f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        // front stand rallying
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(14.00, -1.10, 2.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 5.90f, 0.05f));
        rotateYMatrix_b1 = glm::rotate(identityMatrix, glm::radians(-25.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model_b1 = translateMatrix_b1 * rotateYMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        // front stand (/)
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(15.00, -1.10, 2.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 4.10f, 0.05f));
        rotateYMatrix_b1 = glm::rotate(identityMatrix, glm::radians(-20.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model_b1 = translateMatrix_b1 * rotateYMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        // front left stand (|)
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(16.50, -1.10, 2.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 5.40f, 0.05f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        // front upper beam (---)
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(16.30, 4.10, 2.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(2.50f, .20f, 0.05f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        // front right stand (|)
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(18.80, -1.10, 2.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 5.40f, 0.05f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        // lower beam (---)
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(16.30, 2.60, .60));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(2.50f, .20f, 2.0f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //slipper
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(18.70, 2.70, .60));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(4.45f, .10f, 2.0f));
        rotateYMatrix_b1 = glm::rotate(identityMatrix, glm::radians(-60.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model_b1 = translateMatrix_b1 * rotateYMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
       
        //slipper back handle
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(18.80, 3.30, .50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(5.0f, -.40f, .10f));
        rotateYMatrix_b1 = glm::rotate(identityMatrix, glm::radians(-60.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model_b1 = translateMatrix_b1 * rotateYMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //slipper front handle
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(18.80, 3.30, 2.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(5.0f, -.40f, .10f));
        rotateYMatrix_b1 = glm::rotate(identityMatrix, glm::radians(-60.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model_b1 = translateMatrix_b1 * rotateYMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //stairs
        //1
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(15.0, -.60, .50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.10f, -.10f, 2.0f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //2
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(15.20, -0.10, .50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.10f, -.10f, 2.0f));
        rotateYMatrix_b1 = glm::rotate(identityMatrix, glm::radians(-20.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model_b1 = translateMatrix_b1 * rotateYMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //3
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(15.40, 0.40, .50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.10f, -0.10f, 2.0f));
        rotateYMatrix_b1 = glm::rotate(identityMatrix, glm::radians(-20.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model_b1 = translateMatrix_b1 * rotateYMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //4
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(15.60, 0.90, .50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.10f, -0.10f, 2.0f));
        rotateYMatrix_b1 = glm::rotate(identityMatrix, glm::radians(-20.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model_b1 = translateMatrix_b1 * rotateYMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //5
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(15.80, 1.40, .50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.10f, -.10f, 2.0f));
        rotateYMatrix_b1 = glm::rotate(identityMatrix, glm::radians(-20.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model_b1 = translateMatrix_b1 * rotateYMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //6
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(15.90, 1.90, .50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.10f, -.10f, 2.0f));
        rotateYMatrix_b1 = glm::rotate(identityMatrix, glm::radians(-20.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model_b1 = translateMatrix_b1 * rotateYMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //7
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(16.10, 2.40, .50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.10f, -.10f, 2.0f));
        rotateYMatrix_b1 = glm::rotate(identityMatrix, glm::radians(-20.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model_b1 = translateMatrix_b1 * rotateYMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //rallying pillar
          //back1
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(14.50, -1.10, .50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.10f, 1.50f, .10f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

         //back2
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(15.20, -0.10, .50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.10f, 1.90f, .10f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //back3
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(15.80, 1.40, .50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.10f, 1.80f, .10f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //front1
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(14.50, -1.10, 2.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.10f, 1.50f, .10f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);


        //front2
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(15.20, -0.10, 2.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.10f, 1.90f, .10f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //front3
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(15.80, 1.40, 2.50));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.10f, 1.80f, .10f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);




        /*------------------------------washroom----------------------*/
         //back
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(15.0f, -1.10f, -17.0f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(10.0f, 8.0f, 0.20f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        brick.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //left 
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(15.0f, -1.10f, -17.0f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.20f, 8.0f, 8.0f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        brick.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //right
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(25.0f, -1.10f, -17.0f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.20f, 8.0f, 8.0f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        brick.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //up
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(14.85f, 6.70f, -17.0f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(10.50f, .30f, 8.50f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        cement.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
        //floor
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(14.85f, -1.10f, -17.0f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(10.50f, .10f, 8.0f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        cement.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
        // mirror
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(17.0f, 2.80f, -16.80f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(2.0f, 2.50f, 0.20f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        mirror.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
        //door left
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(15.0f, -1.10f, -9.0f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.0f + door, 8.0f, .20f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        partex1.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
        //door right
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(25.0f, -1.10f, -9.0f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.0f - door, 8.0f, .20f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        partex1.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        if (flag_door == 1)
        {
            door = door + 0.08;
            if (door >= 5)
            {
                flag_door = 21;
            }
        }
        if (flag_door == 2)
        {
            door = door - 0.08;
            if (door <= 0)
            {
                flag_door = 4;
            }
        }


        /*----------------------------shop------------------------------*/
         //back
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-15.0f, -1.10f, -17.0f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(20.0f, 8.0f, 0.20f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        brick.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

         //left 
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-15.0f, -1.10f, -17.0f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.20f, 8.0f, 8.0f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        brick.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //right
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(5.0f, -1.10f, -17.0f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.20f, 8.0f, 8.0f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        brick.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //up
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-15.25f, 6.70f, -17.0f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(20.50f, .30f, 8.50f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        cement.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
        //floor
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-15.25f, -1.10f, -17.0f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(20.50f, .05f, 8.50f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        cement.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //shatter
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-15.0f, 7.0f, -9.0f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(20.0f, 0.0f + dyShop, 0.20f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        shatter.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
        if (flagShop == 1)
        {
            dyShop = dyShop - 0.05;
            if (dyShop <= -8.3)
            {
                flagShop = 21;
            }

        }
        if (flagShop == 2)
        {
            dyShop = dyShop + 0.05;
            if (dyShop >= 0)
            {
                flagShop = 3;
            }
        }
            //back
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-14.50, -1.0, -16.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(5.0f, 4.0f, 3.f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            food.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //back
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-9.0, -1.0, -16.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(4.0f, 6.0f, 3.f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            freeze.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
//rak3
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-4.20, -1.0, -16.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(4.0f, 6.0f, 3.f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            drink.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //counter
            //front
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-.80f, -1.10f, -12.50f));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(5.50f, 3.0f, 2.20f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            nestle.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        /*------------------------seating space----------------------*/
            //table1 top
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-12.20f, .90f, -2.50f));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(5.0f, .20f, 3.50f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            // table1 left
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-11.50f, -1.10f, -2.50f));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.20f, 2.0f, 3.50f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //table1 right
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-8.20f, -1.10f, -2.50f));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.20f, 2.0f, 3.50f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //table2 top
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-12.20f, .90f, 8.0f));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(5.0f, .20f, 3.50f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            // table2 left
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-11.50f, -1.10f, 8.0f));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.20f, 2.0f, 3.50f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //table2 right
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-8.20f, -1.10f, 8.0f));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.20f, 2.0f, 3.50f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //table3 top
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-12.20f, .90f, 18.0f));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(5.0f, .20f, 3.50f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //table3 left
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-11.50f, -1.10f, 18.0f));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.20f, 2.0f, 3.50f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //table3 right
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-8.20f, -1.10f, 18.0f));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.20f, 2.0f, 3.50f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //chair1
            // left
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-10.50, -1.10, -4.250));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 1.0f, 1.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            partex1.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //right
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-9.0, -1.10, -4.250));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 1.0f, 1.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            partex1.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //seat
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-10.70, -.10, -4.25));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(1.70f, 0.20f, 1.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            partex1.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            // chair2
           // left
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-10.50, -1.10, 1.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 1.0f, 1.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            partex1.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //right
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-9.0, -1.10, 1.5));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 1.0f, 1.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            partex1.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //seat
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-10.70, -.10, 1.50));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(1.70f, 0.20f, 1.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            partex1.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            // chair3
           // left
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-10.50, -1.10, 6.250));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 1.0f, 1.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            partex1.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //right
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-9.0, -1.10, 6.250));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 1.0f, 1.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            partex1.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //seat
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-10.70, -.10, 6.25));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(1.70f, 0.20f, 1.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            partex1.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            // chair4
           // left
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-10.50, -1.10, 12.0));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 1.0f, 1.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            partex1.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //right
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-9.0, -1.10, 12.0));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 1.0f, 1.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            partex1.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //seat
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-10.70, -.10, 12.0));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(1.70f, 0.20f, 1.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            partex1.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

             // chair5
            // left
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-10.50, -1.10, 16.250));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 1.0f, 1.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            partex1.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //right
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-9.0, -1.10, 16.250));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 1.0f, 1.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            partex1.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //seat
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-10.70, -.10, 16.25));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(1.70f, 0.20f, 1.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            partex1.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            // chair6
           // left
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-10.50, -1.10, 22.0));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 1.0f, 1.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            partex1.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //right
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-9.0, -1.10, 22.0));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 1.0f, 1.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            partex1.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //seat
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-10.70, -.10, 22.0));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(1.70f, 0.20f, 1.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            partex1.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        /*-----------------------bridge---------------------------*/
            //top1
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-6.60f, -.60f, 11.75f));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(5.10f, .20f, 3.50f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            cement.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //left1
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-7.150f, -1.10f, 11.750f));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.20f, .90f, 3.50f));
            rotateZMatrix_b1 = glm::rotate(identityMatrix, glm::radians(-38.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            model_b1 = translateMatrix_b1 * rotateZMatrix_b1 *scaleMatrix_b1;
            cement.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //right1
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-1.25f, -1.10f, 11.75f));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.20f, .80f, 3.50f));
            rotateZMatrix_b1 = glm::rotate(identityMatrix, glm::radians(40.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            model_b1 = translateMatrix_b1 * rotateZMatrix_b1 * scaleMatrix_b1;
            cement.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //top2
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(27.60f, -.60f, 11.75f));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(5.10f, .20f, 3.50f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            cement.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //left2
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(27.05f, -1.10f, 11.750f));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.20f, .90f, 3.50f));
            rotateZMatrix_b1 = glm::rotate(identityMatrix, glm::radians(-38.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            model_b1 = translateMatrix_b1 * rotateZMatrix_b1 * scaleMatrix_b1;
            cement.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //right2
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(33.0f, -1.10f, 11.75f));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.20f, .80f, 3.50f));
            rotateZMatrix_b1 = glm::rotate(identityMatrix, glm::radians(40.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            model_b1 = translateMatrix_b1 * rotateZMatrix_b1 * scaleMatrix_b1;
            cement.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        /*-------------------------------Train---------------------------------*/
            //train line
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(35.0, -1.0, -18.0));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(5.50f, 0.01f, 45.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            railLine.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //train
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(36.35, -.80, -18.0 + dzt));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(3.0f, 2.0f, 3.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            bluetrain.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(36.35, -.80, -14.850 + dzt));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(3.0f, 2.0f, 3.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            yellowtrain.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(36.35, -.80, -11.7 + dzt));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(3.0f, 2.0f, 3.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            greentrain.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(36.35, -.80, -8.55 + dzt));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(3.0f, 2.0f, 3.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            redtrain.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            if (flag_train == 1)
            {
                dzt = dzt + 0.15;
                if (dzt >= 32.5)
                {
                    flag_train = 2;
                }

            }
            if (flag_train == 2)
            {
                dzt = dzt - 0.15;
                if (dzt <= 0)
                {
                    flag_train = 5;
                }
            }
         /*----------------------Ride_6(Rocket)---------------*/
            //handle 1
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(5.50f, 0.0f + ds1, 25.50f ));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.50f, .10f, -4.0f - ds));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            stick.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

             //seat1 top
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(4.50f, 0.10f + ds1, 23.50f + ds));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(2.50f, .10f, 2.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
            //seat1 back left
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(4.50f, 0.0f + ds1, 23.50f + ds));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.80f, 1.0f, .10f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
            //seat1 front left
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(4.50f, 0.0f + ds1, 25.40f + ds));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.80f, 1.0f, .10f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
            //seat1 back right
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(6.90f, 0.0f + ds1, 23.50f + ds));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-.80f, 1.0f, .10f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
            //seat1 front right
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(6.90f, 0.0f + ds1, 25.40f + ds));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-.80f, 1.0f, .10f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
            // seat1 left
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(4.50f, 0.0f + ds1, 23.50f + ds));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.10f, 1.0f, 2.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
            //seat1 right
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(6.90f, 0.0f + ds1, 23.50f + ds));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.10f, 1.0f, 2.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //handle2
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(5.50f, 0.0f + ds1, 16.50f));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.50f, .10f, 4.0f + ds));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            stick.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
            //seat2 top
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(4.50f, .10f + ds1, 16.50f - ds));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(2.50f, .10f, 2.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
            //seat2 back left
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(4.50f, .0f + ds1, 16.50f - ds));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.80f, 1.0f, .10f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
            //seat2 front left
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(4.50f, .0f + ds1, 18.40f - ds));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.80f, 1.0f, .10f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
            //seat2 back right
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(6.90f, .0f + ds1, 16.50f - ds));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-.80f, 1.0f, .10f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
            //seat2 front right
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(6.90f, .0f + ds1, 18.40f - ds));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-.80f, 1.0f, .10f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
            // seat2 left
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(4.50f, .0f + ds1, 16.50f - ds));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.10f, 1.0f, 2.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
            //seat2 right
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(6.90f, .0f + ds1, 16.50f - ds));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.10f, 1.0f, 2.0f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //handle3
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(0.50f, 0.0f + ds1, 21.0f));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(5.0f +ds, .10f, .50f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            stick.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
            //seat3 top
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(.50f - ds, .10f + ds1, 20.0f));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(2.0f, .10f, 2.50f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
            //seat3 back left
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(.50f - ds, .0f + ds1, 20.0f));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.10f, 1.0f, .80f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
            //seat3 front left
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(.50f - ds, .0f + ds1, 22.50f));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.10f, 1.0f, -.80f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
            //seat3 back right
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(2.450f - ds, .0f + ds1, 20.0f));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.10f, 1.0f, .80f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
            //seat3 front right
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(2.450f - ds, .0f + ds1, 22.50f));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.10f, 1.0f, -.80f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
            // seat3 left
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(.50f - ds, .0f + ds1, 20.0f));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(2.0f, 1.0f, .10f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
            //seat3 right
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(.50f - ds, .0f + ds1, 22.50f));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(2.0f, 1.0f, .10f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

            //handle4
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(10.0f, 0.0f + ds1, 21.0f));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-5.0f + ds, .10f, .50f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            stick.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
            //seat4 top
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(8.0f + ds, .10f + ds1, 20.0f));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(2.0f, .10f, 2.50f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
            //seat4 back left
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(8.0f + ds, .0f + ds1, 20.0f));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.10f, 1.0f, .80f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
            //seat4 front left
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(8.0f + ds, .0f + ds1, 22.50f));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.10f, 1.0f, -.80f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
            //seat4 back right
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(9.950f + ds, .0f + ds1, 20.0f));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.10f, 1.0f, .80f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
            //seat4 front right
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(9.950f + ds, .0f + ds1, 22.50f));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.10f, 1.0f, -.80f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
            // seat4 left
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(8.0f + ds, .0f + ds1, 20.0f));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(2.0f, 1.0f, .10f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
            //seat4 right
            translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(8.0f + ds, .0f + ds1, 22.50f));
            scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(2.0f, 1.0f, .10f));
            model_b1 = translateMatrix_b1 * scaleMatrix_b1;
            wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);



            if (flag_rkt == 1)
            {
                ds = ds + 0.05;
                if (ds >= 2)
                {
                    flag_rkt = 2;
                }

            }
            if (flag_rkt == 2)
            {
                ds1 = ds1 + 0.02;
                if (ds1 >= 2.5)
                {
                    flag_rkt = 3;
                }

            }
            
            if (flag_rkt == 3)
            {
                ds = ds - 0.05;
                if (ds <= 0)
                {
                    flag_rkt = 4;
                }
            }
            if (flag_rkt == 4)
            {
                ds = ds + 0.05;
                if (ds >= 2)
                {
                    flag_rkt = 51;
                }

            }
            if (flag_rkt == 51)
            {
                ds1 = ds1 + 0.02;
                if (ds1 >= 4)
                {
                    flag_rkt = 6;
                }

            }
            if (flag_rkt == 6)
            {
                ds = ds - 0.05;
                if (ds <= 0)
                {
                    flag_rkt = 7;
                }
            }
            if (flag_rkt == 7)
            {
                ds1 = ds1 - 0.02;
                if (ds1 <= 3)
                {
                    flag_rkt = 8;
                }
            }
            if (flag_rkt == 8)
            {
                ds = ds + 0.05;
                if (ds >= 2)
                {
                    flag_rkt = 9;
                }

            }
            if (flag_rkt == 9)
            {
                ds = ds - 0.05;
                if (ds <= 0)
                {
                    flag_rkt = 10;
                }
            }
            if (flag_rkt == 10)
            {
                ds1 = ds1 - 0.02;
                if (ds1 <= 1)
                {
                    flag_rkt = 11;
                }
            }
            if (flag_rkt == 11)
            {
                ds = ds + 0.05;
                if (ds >= 2)
                {
                    flag_rkt = 12;
                }

            }
            if (flag_rkt == 12)
            {
                ds = ds - 0.05;
                if (ds <= 0)
                {
                    flag_rkt = 13;
                }
            }
          
           

        /*------------------------------------------------BENCHES-------------------------------------------*/

        //sofa1
            //base
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(4.0f, -1.10f, -1.30f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(3.50f, 1.0f, 1.60f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
           
        //sofa1 uporer part
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(4.0f, -1.10f, -1.30f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(3.50f, 2.10f, .20f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        bench.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        // sofa2 
           // base
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(24.30f, -1.10f, -1.25f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(1.6f, 1.0f, 3.50f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //sofa2 uporer part
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(25.70f, -1.10f, -1.25f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.20f, 2.10f, 3.50f));
        //scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(.20f, 2.10f, 5.0f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        bench.drawCubeWithTexture(lightingShaderWithTexture, model_b1);


        // sofa3
                  // base
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-0.50f, -1.10f, 5.50f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(1.60f, 1.0f, 3.50f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
          
        //sofa3 uporer part
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-0.50f, -1.10f, 5.50f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.20f, 2.10f, 3.50f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        bench.drawCubeWithTexture(lightingShaderWithTexture, model_b1);


        // sofa4
                  // base
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-0.50f, -1.10f, 17.0f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(1.60f, 1.0f, 3.50f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        //wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

          
        //sofa4 uporer part
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-0.50f, -1.10f, 17.0f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.20f, 2.10f, 3.50f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        //bench.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        ////// sofa5
        //     // base
        //translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(24.30f, -1.10f, 5.50f));
        //scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(1.60f, 1.0f, 3.50f));
        //model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        //wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //    //sofa5 uporer part
        //translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(25.70f, -1.10f, 5.50f));
        //scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.20f, 2.10f, 3.50f));
        //model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        //bench.drawCubeWithTexture(lightingShaderWithTexture, model_b1);


        // sofa6
                  // base
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(24.30f, -1.10f, 19.0f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(1.60f, 1.0f, 3.50f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        wood.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        //sofa6 uporer part
        translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(25.70f, -1.10f, 19.0f));
        scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(0.20f, 2.10f, 3.50f));
        model_b1 = translateMatrix_b1 * scaleMatrix_b1;
        bench.drawCubeWithTexture(lightingShaderWithTexture, model_b1);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &cubeEBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}




// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

   /* if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        if (rotateAxis_X) rotateAngle_X -= 0.1;
        else if (rotateAxis_Y) rotateAngle_Y -= 0.1;
        else rotateAngle_Z -= 0.1;
    }*/
   // if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) translate_Y += 0.001;
   // if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) translate_Y -= 0.001;
    //if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) translate_X += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) translate_X -= 0.001;
    //if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) translate_Z += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) translate_Z -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) scale_X += 0.001;
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) scale_X -= 0.001;
    //if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) scale_Y += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) scale_Y -= 0.001;
    //if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) scale_Z += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) scale_Z -= 0.001;

    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
    {
        flag = 1;
    }
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
    {
        swingFlag = 1;
    }
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
    {
        flagR2 = 1;
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        flagShop = 1;
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        flagShop = 2;
    }
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
    {
        flag_ss = 1;
    }
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
    {
        flag_ex = 1;
    }
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
    {
        flag3 = 1;
    }

    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
    {
        flag_door = 1;
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        flag_door = 2;
    }

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
    {
        flag_train = 1;
    }
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
    {
        flag_rkt = 1;
    }

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        rotateAngle_X += 0.1;
        rotateAxis_X = 1.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
    {
        rotateAngle_Y += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 1.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        rotateAngle_Z += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 1.0;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camera.ProcessKeyboard(UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        camera.ProcessKeyboard(DOWN, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        camera.ProcessKeyboard(P_UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        camera.ProcessKeyboard(P_DOWN, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
        camera.ProcessKeyboard(Y_LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
        camera.ProcessKeyboard(Y_RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        camera.ProcessKeyboard(R_LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        camera.ProcessKeyboard(R_RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        pointlight1.turnOn();
        pointlight3.turnOn();
        pointlight4.turnOn();
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        pointlight1.turnOff();
        pointlight3.turnOff();
        pointlight4.turnOff();

    }
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
    {
        pointlight1.turnDiffuseOn();
        pointlight3.turnDiffuseOn();
        pointlight4.turnDiffuseOn();
        spotLight.turnDiffuseOn();
        dirLight.turnDiffuseOn();

    }
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
    {
        
        pointlight1.turnOff();
        pointlight3.turnOff();
        pointlight4.turnOff();
        dirLight.turnOff();
        spotLight.turnOff();

    }

    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        dirLight.turnOn();

    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {
        dirLight.turnOff();
    }
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    {
        spotLight.turnOn();

    }
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
    {
        spotLight.turnOff();
    }
    if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
    {
        pointlight1.turnAmbientOn();
        pointlight3.turnAmbientOn();
        pointlight4.turnAmbientOn();
        spotLight.turnAmbientOn();
        dirLight.turnAmbientOn();
    }
    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
    {
        pointlight1.turnSpecularOn();
        pointlight3.turnSpecularOn();
        pointlight4.turnSpecularOn();
        spotLight.turnSpecularOn();
        dirLight.turnSpecularOn();
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrappingModeS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrappingModeT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilteringModeMin);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilteringModeMax);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

long long nCr(int n, int r)
{
    if (r > n / 2)
        r = n - r; // because C(n, r) == C(n, n - r)
    long long ans = 1;
    int i;

    for (i = 1; i <= r; i++)
    {
        ans *= n - r + i;
        ans /= i;
    }

    return ans;
}

//polynomial interpretation for N points
void BezierCurve(double t, float xy[2], GLfloat ctrlpoints[], int L)
{
    double y = 0;
    double x = 0;
    t = t > 1.0 ? 1.0 : t;
    for (int i = 0; i < L + 1; i++)
    {
        long long ncr = nCr(L, i);
        double oneMinusTpow = pow(1 - t, double(L - i));
        double tPow = pow(t, double(i));
        double coef = oneMinusTpow * tPow * ncr;
        x += coef * ctrlpoints[i * 3];
        y += coef * ctrlpoints[(i * 3) + 1];

    }
    xy[0] = float(x);
    xy[1] = float(y);
}

unsigned int hollowBezier(GLfloat ctrlpoints[], int L)
{
    int i, j;
    float x, y, z, r;                //current coordinates
    float theta;
    float nx, ny, nz, lengthInv;    // vertex normal


    const float dtheta = 2 * pi / ntheta;        //angular step size

    float t = 0;
    float dt = 1.0 / nt;
    float xy[2];

    for (i = 0; i <= nt; ++i)              //step through y
    {
        BezierCurve(t, xy, ctrlpoints, L);
        r = xy[0];
        y = xy[1];
        theta = 0;
        t += dt;
        lengthInv = 1.0 / r;

        for (j = 0; j <= ntheta; ++j)
        {
            double cosa = cos(theta);
            double sina = sin(theta);
            z = r * cosa;
            x = r * sina;

            coordinates.push_back(x);
            coordinates.push_back(y);
            coordinates.push_back(z);

            // normalized vertex normal (nx, ny, nz)
            // center point of the circle (0,y,0)
            nx = (x - 0) * lengthInv;
            ny = (y - y) * lengthInv;
            nz = (z - 0) * lengthInv;

            normals.push_back(nx);
            normals.push_back(ny);
            normals.push_back(nz);

            theta += dtheta;
        }
    }

    // generate index list of triangles
    // k1--k1+1
    // |  / |
    // | /  |
    // k2--k2+1

    int k1, k2;
    for (int i = 0; i < nt; ++i)
    {
        k1 = i * (ntheta + 1);     // beginning of current stack
        k2 = k1 + ntheta + 1;      // beginning of next stack

        for (int j = 0; j < ntheta; ++j, ++k1, ++k2)
        {
            // k1 => k2 => k1+1
            indices.push_back(k1);
            indices.push_back(k2);
            indices.push_back(k1 + 1);

            // k1+1 => k2 => k2+1
            indices.push_back(k1 + 1);
            indices.push_back(k2);
            indices.push_back(k2 + 1);
        }
    }

    size_t count = coordinates.size();
    for (int i = 0; i < count; i += 3)
    {
        vertices.push_back(coordinates[i]);
        vertices.push_back(coordinates[i + 1]);
        vertices.push_back(coordinates[i + 2]);

        vertices.push_back(normals[i]);
        vertices.push_back(normals[i + 1]);
        vertices.push_back(normals[i + 2]);
    }

    unsigned int bezierVAO;
    glGenVertexArrays(1, &bezierVAO);
    glBindVertexArray(bezierVAO);

    // create VBO to copy vertex data to VBO
    unsigned int bezierVBO;
    glGenBuffers(1, &bezierVBO);
    glBindBuffer(GL_ARRAY_BUFFER, bezierVBO);           // for vertex data
    glBufferData(GL_ARRAY_BUFFER,                   // target
        (unsigned int)vertices.size() * sizeof(float), // data size, # of bytes
        vertices.data(),   // ptr to vertex data
        GL_STATIC_DRAW);                   // usage

    // create EBO to copy index data
    unsigned int bezierEBO;
    glGenBuffers(1, &bezierEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bezierEBO);   // for index data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,           // target
        (unsigned int)indices.size() * sizeof(unsigned int),             // data size, # of bytes
        indices.data(),               // ptr to index data
        GL_STATIC_DRAW);                   // usage

    // activate attrib arrays
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // set attrib arrays with stride and offset
    int stride = 24;     // should be 24 bytes
    glVertexAttribPointer(0, 3, GL_FLOAT, false, stride, (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, stride, (void*)(sizeof(float) * 3));

    // unbind VAO, VBO and EBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return bezierVAO;
}