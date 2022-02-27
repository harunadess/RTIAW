#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <vector>
#include "hittable.hpp"

template <class C, typename T>
class hittableList //:public hittable
{
public:
	hittableList() {}
	hittableList(C object) { add(object); }

	void clear() { objects.clear(); }
	void add(C object) { objects.push_back(object); }

	bool hit(const ray<T> &r, T tMin, T tMax, hitRecord<T> &rec) const;

	std::vector<C> objects;
};

template <class C, typename T>
bool hittableList<C, T>::hit(const ray<T> &r, T tMin, T tMax, hitRecord<T> &rec) const
{
	hitRecord<T> tempRec;
	bool didHit = false;
	auto closest = tMax;

	for(const auto& object: objects)
	{
		if(object.hit(r, tMin, closest, tempRec))
		{
			didHit = true;
			closest = tempRec.t;
			rec = tempRec;
		}
	}

	return didHit;
}

#endif // !HITTABLE_LIST_H
