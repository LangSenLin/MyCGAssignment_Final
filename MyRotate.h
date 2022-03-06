

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>
#include <vector>

using namespace std;
/*
 *   类名称：myRotate
 *   类功能：三维信息绕x/y/z轴旋转并返回结果
 */
namespace MyRotate {
	static glm::vec3 RotateX(glm::vec3 target, float angle) {
		angle = glm::radians(angle);
		glm::mat3 matrix(0.0f);
		matrix[0][0] = 1.0f;
		matrix[1][1] = cos(angle);
		matrix[1][2] = sin(angle);
		matrix[2][1] = -sin(angle);
		matrix[2][2] = cos(angle);
		glm::vec3 ret = matrix * target;
		return ret;
	}

	static glm::vec3 RotateY(glm::vec3 target, float angle) {
		angle = glm::radians(angle);
		glm::mat3 matrix(0.0f);
		matrix[0][0] = cos(angle);
		matrix[0][2] = -sin(angle);
		matrix[1][1] = 1.0f;
		matrix[2][0] = sin(angle);
		matrix[2][2] = cos(angle);
		glm::vec3 ret = matrix * target;
		return ret;
	}

	static glm::vec3 RotateZ(glm::vec3 target, float angle) {
		angle = glm::radians(angle);
		glm::mat3 matrix(0.0f);
		matrix[0][0] = cos(angle);
		matrix[0][1] = sin(angle);
		matrix[1][0] = -sin(angle);
		matrix[1][1] = cos(angle);
		matrix[2][2] = 1.0f;
		glm::vec3 ret = matrix * target;
		return ret;
	}
}
