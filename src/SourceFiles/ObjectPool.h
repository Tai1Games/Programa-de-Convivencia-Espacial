//#pragma once
//#include <cassert>
//#include <list>
//#include <array>
//#include <vector>
//#include <functional>
//
//using namespace std;
//
//template<typename T>
//class ObjectPool {
//private:
//	vector<T*> objs_;
//	std::function<bool(T*)> inUseF_;
//
//public:
//	ObjectPool(std::function<bool(T*)> f) {
//		inUseF_ = f;
//		objs_ = vector<T*>();
//	}
//
//	virtual ~ObjectPool() {
//		for (T* o: objs_) delete o;
//		objs_.clear();
//	}
//
//	T* getObj() {
//		for (auto o : objs_) {
//			if (!inUseF_(o))
//				return o;
//		}
//		return nullptr;
//	}
//
//	const vector<T*>& getPool() {
//		return objs_;
//	}
//};
#pragma once
#include <array>
#include <vector>
#include <functional>

// The size of the pool is static, provided by the template parameter.
// We can instead pass it to the constructor so we can decide the size
// the pool dynamically, but then objs_ cannot be a static array
//
template<typename T, int SIZE>
class ObjectPool {
public:
	// f is a lambda expression used to check if an object is in use,
	// this way we avoid assuming that T has a method with a specific
	// name.
	//
	// Ex: if we use the pool with a class A, whose method inUse is the
	// one that checks if the object is in use, we can use for f:
	//
	//     [](A *o) { return o->inUse(); }
	//
	ObjectPool(std::function<bool(T*)> f) {
		inUseF_ = f;
		for (auto& b : objs_) {
			objsPtrs_.push_back(&b);
		}
	}

	virtual ~ObjectPool() {
	}

	T* getObj() {
		for (auto& o : objs_) {
			if (!inUseF_(&o))
				return &o;
		}
		return nullptr;
	}

	const std::vector<T*>& getPool() {
		return objsPtrs_;
	}

private:
	std::function<bool(T*)> inUseF_;
	std::array<T, SIZE> objs_;
	std::vector<T*> objsPtrs_;
};