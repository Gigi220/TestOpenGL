// 学学学
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Visual
{
	class Transform
	{
	public:
		Transform() = default;
		Transform(const glm::vec3& pos) { SetPosition3D(pos); }
		Transform(const glm::vec3& pos, const glm::vec3& rotation) { SetPosition3D(pos); }
		Transform(const Transform& transform) { SetPosition3D(transform._pos); }

		const glm::vec3& GetPosition3D() const { return _pos; }
		void SetPosition3D(const glm::vec3& pos) 
		{ 
			_pos = pos;
			OnModelMatrixChanged();
		}

		const glm::vec3& GetRotation() const { return _rotation; }
		void SetRotation(const glm::vec3& rotation)
		{
			_rotation = rotation;
			OnModelMatrixChanged();
		}

		const glm::mat4x4& GetModelMatrix() const { return _matrix; }
		void SetModelMatrix(const glm::mat4x4& matrix) { _matrix = matrix; }
		void OnModelMatrixChanged()
		{ 
			_matrix = glm::mat4x4(1.0f);
			_matrix = glm::translate(_matrix, _pos);
			_matrix = glm::rotate(_matrix, glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
			_matrix = glm::rotate(_matrix, glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
			_matrix = glm::rotate(_matrix, glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		}

	private:
		glm::vec3 _pos = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 _rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::mat4x4 _matrix = glm::mat4x4(1.0f);
	};
}
