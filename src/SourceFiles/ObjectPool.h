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