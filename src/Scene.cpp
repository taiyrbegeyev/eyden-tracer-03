#include <fstream>

#include "PrimTriangle.h"
#include "ShaderPhong.h"
#include "Scene.h"
#include "ShaderEyelight.h"

void CScene::ParseOBJ(const std::string& name_of_file) {
	std::cout << "OBJFile : " << name_of_file << std::endl;

	std::shared_ptr<IShader> pShader = std::make_shared<CShaderEyelight>(RGB(1, 1, 1));
	std::vector <unsigned int> vertex_indices;
	std::vector <Vec3f> temp_vertices;

	std::ifstream file;
	// open the file
	file.open(name_of_file);
	if (!file.is_open()) {
		std::cout << "Error opening the file" << std::endl;
		return;
	}

	while(!file.eof()) {
		char line = file.get();
		if (line == 'v') {
			Vec3f vertex;
			float x, y ,z;
			file >> x >> y >> z;
			vertex[0] = x * 99.99f;
			vertex[1] = y * 99.99f;
			vertex[2] = z * 99.99f;
			temp_vertices.push_back(vertex);
		}
		else if(line == 'f') {
			unsigned int vertex_index[3];
			unsigned int a, b, c;
			file >>a >> b >> c;
			vertex_index[0] = a;
			vertex_index[1] = b;
			vertex_index[2] = c;
			vertex_indices.push_back(vertex_index[0]);
			vertex_indices.push_back(vertex_index[1]);
			vertex_indices.push_back(vertex_index[2]);
		}
	}

	int i = 0;
	while(i < vertex_indices.size()) {
		Vec3f v1, v2, v3;
		v1 = temp_vertices[vertex_indices[i] - 1];
		i++;
		v2 = temp_vertices[vertex_indices[i] - 1];
		i++;
		v3 = temp_vertices[vertex_indices[i] - 1];
		i++;
		Add(std::make_shared<CPrimTriangle>(v1, v2, v3,pShader));
	}

	// close the file
	file.close();
	std::cout << "Parsing is finished" << std::endl;

	return;
}
