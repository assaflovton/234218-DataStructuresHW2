#ifndef AVL_COURSE_H_
#define AVL_COURSE_H_
#include "HashTable.h"
#include "Class.h"

int getId(Class c)
{
    return c.class_id;
}

class Course
{
public:
    int course_id;
    HashTable<Class>* classes_array;//hash table of all the classes assigned to this course
    class ALLOC_ERROR {};
    Course(int course_id) : course_id(course_id), classes_array(new HashTable<Class>(&(getId)))
    {}

    Course() :course_id(0), classes_array(NULL) {}

    Course(const Course& c) :course_id(c.course_id) {
        classes_array = new HashTable<Class>(&getId);
        (*classes_array) = *(c.classes_array);
    }
    ~Course() {}

    Course& operator=(const Course& c)
    {
        if (this != &c)
        {
            this->course_id = c.course_id;
            (*classes_array) = *(c.classes_array);
        }
        return *this;
    }
    bool operator==(const Course& c) const
    {
        return (this->course_id == c.course_id);
    }
    bool operator!=(const Course& c) const
    {
        return !((*this) == c);
    }
    bool operator<=(const Course& c) const
    {
        return (this->course_id) >= c.course_id;
    }

    bool operator>=(const Course& c) const
    {
        return c <= (*this);
    }

    bool operator<(const Course& c) const
    {
        return (this->course_id) > c.course_id;
    }
    bool operator>(const Course& c) const
    {
        return c < (*this);
    }
    friend std::ostream& operator<<(std::ostream& os, const Course& c)
    {
        std::cout << "\nCourse:" << c.course_id << "  ";
        c.classes_array->print();
        std::cout << "\n";
        return os;
    }
};

#endif //AVL_COURSE_H_