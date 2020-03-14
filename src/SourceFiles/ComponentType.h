#pragma once
#include <ctime>
#include "checkML.h"


namespace ComponentType {

	using CmpIdType = std::size_t;

	enum CmpId : CmpIdType {
		//Vayan metiendo aqui sus componentes segun lo hagan
		Transform = 0,
		Health,
		Viewer,
		Collider,
		HealthViewer,
		Tilemap,
		// don't touch the rest of this enum, it is to identify the max
		// number of components
		_LastCmptId_
	};

	constexpr std::size_t maxComponents = _LastCmptId_;

	// these two should be used to get a component via the field
	// entity_
#define GETCMP2_(id,type)  GETCMP3(entity_,id,type)
#define GETCMP1_(type)     GETCMP3(entity_,ComponentType::type,type)

// these two should be used to get a component via an
// entity e provided as a parameter
#define GETCMP2(e,type) GETCMP3(e,ComponentType::type,type)
#define GETCMP3(e,id,type) e->getComponent<type>(id)

}
