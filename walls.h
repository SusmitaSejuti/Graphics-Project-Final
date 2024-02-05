#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "drawcube.h"


void walls(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    ///glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    glm::mat4 translateMatrix_b1, rotateXMatrix_b1, rotateYMatrix_b1, rotateZMatrix_b1, scaleMatrix_b1, model_b1;

    /*--------------------------RIVER SIDE FENCHING------------------------*/
    //left side(1-10)
    // stand1
    translateMatrix_b1 = glm::translate(identityMatrix, glm::vec3(-3.50, -1.10, -1.50));
    scaleMatrix_b1 = glm::scale(identityMatrix, glm::vec3(-0.20f, 2.50f, 0.05f));
    model_b1 = translateMatrix_b1 * scaleMatrix_b1;
   // metal.drawCubeWithTexture(lightingShaderWithTexture, model_b1);
    drawCube(cubeVAO, lightingShader, model_b1, 0.3725, 0.7451f, 0.8471f);//37, 150, 190

    //Ceiling
    //translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.5, 4.5, -5.5));
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(20, .5, 20));
    //model = alTogether * translateMatrix * scaleMatrix;
    //drawCube(cubeVAO, lightingShader, model, 0.3725, 0.7451f, 0.8471f);//37, 150, 190
    
    //Floor
    //translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5, -2.5, -7.5));
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(20, .5, 20));
    //model = alTogether*translateMatrix * scaleMatrix;
    //drawCube(cubeVAO, lightingShader, model, 0.0, 0.9f, 0.0f);//12, 100, 9, 1

    //Right wall
    /*translateMatrix = glm::translate(identityMatrix, glm::vec3(5, -0.45, -5.5));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25, 8, 10));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.3725, 0.7451f, 0.8471f);*/

    //Left wall
   /* translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.5, -0.45, 4.5));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25, 8, -10));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.3725, 0.7451f, 0.8471f);*/
    
    //Back wall
    //translateMatrix = glm::translate(identityMatrix, glm::vec3(-6.5, -0.45, -6.5));
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(20, 8, .2));
    //model = alTogether * translateMatrix * scaleMatrix;
    //drawCube(cubeVAO, lightingShader, model, 0.3725, 0.7451f, 0.8471f);//118, 181, 197//210, 236, 243, 1//95, 190, 216, 1
    //

    
}


