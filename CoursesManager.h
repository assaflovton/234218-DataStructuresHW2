#ifndef DS_H
#define DS_H
#include "Class.h"
#include "Course.h"
#include "RankTree.h"
#include "HashTable.h"

int getId(Course c)
{
    return c.course_id;
}

class Boom {
public:
    HashTable<Course> courses_hash;//hash table of all the courses in the system
    RankTree<Class> classes_tree;//watched classes WAVL tree
    Boom() :courses_hash(HashTable<Course>(&getId)), classes_tree(RankTree<Class>()) {}
    Boom(const Boom& b) :courses_hash(b.courses_hash), classes_tree(b.classes_tree) {}
};



#endif // DS_H
