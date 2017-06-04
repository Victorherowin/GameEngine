#ifndef TRANSFORM
#define TRANSFORM

#include "../Define.hpp"
#include "../Include.hpp"
#include "../GLMInclude.hpp"

#include <list>

namespace Kedama
{
	using namespace std;
	using namespace glm;

	class GameObject;

    enum class SpaceType
    {
      World,Model
    };

	class KEDAMA_API Transform
	{
	public:
		using UpdateListener = function<void(Transform&)>;

        Transform();

        void SetRelativePosition(const vec3& position);
        void SetWorldPosition(const vec3& position);

        void SetRelativeAngle(const quat& angle);
		void SetWorldAngle(const quat& angle);//四元数
        void SetRelativeAngle(const mat3& angle);
        void SetWorldAngle(const mat3& angle);//矩阵

        void SetRelativeMatrix(const mat4& mat);
		void SetWorldMatrix(const mat4& mat);

        void SetScale(float sx,float sy,float sz);

		inline const vec3& GetRelativePosition() { return m_position; }
        inline const quat GetRelativeAngle() { return m_angle; }
		inline const mat4& GetRelativeMatrix() { return m_relative_matrix; }
		inline const vec3& GetScale() { return m_scale; }

		quat GetWorldAngle();
		vec3 GetWorldPosition();
		const mat4& GetWorldMatrix();
		const mat4& GetModelMatrix();

        void Move(const vec3& distance,SpaceType type=SpaceType::Model);
        void Rotate(const quat& angle,SpaceType type=SpaceType::Model);
        void Rotate(const vec3& axis, float rad,SpaceType type=SpaceType::Model);

		void Update();

		void AddUpdateListener(const string& name,const UpdateListener& listener);
		void RemoveUpdateListener(const string& name);

        void AddChildren(Transform* c);
        inline const list<Transform*>& GetChildren()const
        {return m_children;}

        bool RemoveNode(Transform* node,bool disconnect=false);

        inline Transform* GetParent()
        {return m_parent;}

	private:
		void SetChildrenNeedUpdateFlag();
		void UpdateSelf();
		void UpdateChildren();

	protected:
		bool m_need_update = false;
		map<string, UpdateListener> m_listeners;

		//相对位置
		vec3 m_position;
        quat m_angle;
		vec3 m_scale;

		mat4 m_relative_matrix;//相对位置矩阵
		mat4 m_world_matrix;//绝对位置矩阵
		mat4 m_model_matirx;//模型矩阵
        mat4 m_inverse_world_matrix;//世界坐标系逆矩阵
    private:
        Transform* m_parent=nullptr;
        std::list<Transform*> m_children;
	};
}

#endif
