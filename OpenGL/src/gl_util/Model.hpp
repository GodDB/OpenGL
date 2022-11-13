//
//  Model.hpp
//  OpenGL
//
//  Created by beom.93 on 2022/11/13.
//

#ifndef Model_hpp
#define Model_hpp

#include <stdio.h>

#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Shader.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "VertexBufferElement.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Texture.hpp"
#include "Renderer.hpp"

class Model {
    
public :
    Model();
    ~Model();
    
    void loadModel(const std::string& fileName);
    void ClearModel();
    void RenderModel(Shader shader);
    
private:
    void LoadNode(aiNode* node, const aiScene* scene);
    void LoadMesh(aiMesh* mesh, const aiScene* scene);
    void LoadMaterials(const aiScene* scene);

    std::vector<VertexArray*> VAOs;
    std::vector<VertexBuffer*> VBOs;
    std::vector<IndexBuffer*> IBOs;
    std::vector<Texture*> m_TextureList;
    std::vector<unsigned int> m_MeshToTex;
};

#endif /* Model_hpp */
