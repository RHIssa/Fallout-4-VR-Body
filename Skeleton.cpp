#include "Skeleton.h"


namespace F4VRBody
{
	void printMatrix(Matrix44* mat) {
		_MESSAGE("Dump matrix:");
		std::string row = "";
		for (auto i = 0; i < 4; i++) {
			for (auto j = 0; j < 4; j++) {
				row += std::to_string(mat->data[i][j]);
				row += " ";
			}
			_MESSAGE("%s", row.c_str());
			row = "";
		}
	}

	void Skeleton::printChildren(NiNode* child, std::string padding) {
		padding += "....";
		_MESSAGE("%s%s : children = %d : local x = %f : world x = %f : local y = %f : world y = %f : local z = %f : world z = %f", padding.c_str(), child->m_name.c_str(), child->m_children.m_emptyRunStart,
			child->m_localTransform.pos.x, child->m_worldTransform.pos.x,
			child->m_localTransform.pos.y, child->m_worldTransform.pos.y,
			child->m_localTransform.pos.z, child->m_worldTransform.pos.z);

		for (auto i = 0; i < child->m_children.m_emptyRunStart; ++i) {
			auto nextNode = child->m_children.m_data[i] ? child->m_children.m_data[i]->GetAsNiNode() : nullptr;
			if (nextNode) {
				this->printChildren(nextNode, padding);
			}
		}
	}

	void Skeleton::printNodes() {
		// print root node info first
		_MESSAGE("%s : children = %d : local x = %f : world x = %f : local y = %f : world y = %f : local z = %f : world z = %f", _root->m_name.c_str(), _root->m_children.m_emptyRunStart,
			_root->m_localTransform.pos.x, _root->m_worldTransform.pos.x,
			_root->m_localTransform.pos.y, _root->m_worldTransform.pos.y,
			_root->m_localTransform.pos.z, _root->m_worldTransform.pos.z);

		std::string padding = "";

		for (auto i = 0; i < _root->m_children.m_emptyRunStart; ++i) {
			auto nextNode = _root->m_children.m_data[i] ? _root->m_children.m_data[i]->GetAsNiNode() : nullptr;
			if (nextNode) {
				this->printChildren(nextNode, padding);
			}
		}
	}

	void Skeleton::rotateWorld(NiNode *nde) {
		Matrix44* result = new Matrix44();
		Matrix44 mat;

		mat.data[0][0] = -1.0;
		mat.data[0][1] = 0.0;
		mat.data[0][2] = 0.0;
		mat.data[0][3] = 0.0;
		mat.data[1][0] = 0.0;
		mat.data[1][1] = -1.0;
		mat.data[1][2] = 0.0;
		mat.data[1][3] = 0.0;
		mat.data[2][0] = 0.0;
		mat.data[2][1] = 0.0;
		mat.data[2][2] = 1.0;
		mat.data[2][3] = 0.0;
		mat.data[3][0] = 0.0;
		mat.data[3][1] = 0.0;
		mat.data[3][2] = 0.0;
		mat.data[3][3] = 0.0;

		NiMatrix43 *local = (NiMatrix43*)&nde->m_worldTransform.rot;

		result = matrixMultiply(local, result, &mat);

		printMatrix(result);

		delete result;
	}

	void Skeleton::updatePos(NiNode* nde, NiPoint3 offset) {

		nde->m_worldTransform.pos += offset;

		for (auto i = 0; i < nde->m_children.m_emptyRunStart; ++i) {
			auto nextNode = nde->m_children.m_data[i] ? nde->m_children.m_data[i]->GetAsNiNode() : nullptr;
			if (nextNode) {
				this->updatePos(nextNode, offset);
			}
		}
	}

	void Skeleton::projectSkelly(float offsetOutFront) {    // Projects the 3rd person body out in front of the player by offset amount
		NiPoint3 playerLook;
		playerLook.x = _root->m_worldTransform.rot.data[1][0];   // get unit vector pointing straight out in front of the player in player space.   y is forward axis  x is horizontal   since 2x2 rotation z is not used
		playerLook.y = _root->m_worldTransform.rot.data[0][0];
		playerLook.z = 0;

		this->_lookOut.x = -1 * playerLook.x;   // to turn the body to face the player calculate unit vector that points back at player in player space
		this->_lookOut.y = -1 * playerLook.y;

		playerLook *= offsetOutFront;

		this->updatePos(_root, playerLook);   // offset all positions in the skeleton


	}

	Matrix44* Skeleton::matrixMultiply(NiMatrix43* worldMat, Matrix44* retMat, Matrix44* localMat) {
		using func_t = decltype(&Skeleton::matrixMultiply);
		RelocAddr<func_t> func(0x1a8d60);

		Matrix44* mat = func(worldMat, retMat, localMat);
		return mat;
	}

}
