#include "library2.h"
#include "CoursesManager.h" 

//Initializing the Structure with new Empty tree and new Empty size 10 hash table
//O(1) worth case
void* Init()
{
	return (void*)(new Boom());
}
//adding the course to the courses hash table,
//O(1) on avarge - hash table insert is O(1) on avarge.
StatusType AddCourse(void* DS, int courseID)
{
	if (DS == NULL || courseID <= 0)
	{
		return INVALID_INPUT;
	}
	try
	{
		Course new_course = Course(courseID);
		(((Boom*)DS)->courses_hash).insertElem(new_course); //log(number of courses)
	}
	catch (RankTree<Course>::ALLOC_ERROR())
	{
		return ALLOCATION_ERROR;
	}
	catch (Course::ALLOC_ERROR())
	{
		return ALLOCATION_ERROR;
	}
	catch (RankTree<Course>::ALREADY_EXIST())
	{
		return FAILURE;
	}
	catch (...)
	{
		return FAILURE;
	}
	return SUCCESS;
}
//removing the course from the courses hash table and all of his watched classes from the classes tree
//there are m classes and each class remove is log(M) so the final comlexity is m*log(M) as wanted
StatusType RemoveCourse(void* DS, int courseID)
{
	if (DS == NULL || courseID <= 0)
	{
		return INVALID_INPUT;
	}
	try
	{
		Course tmp1(courseID);
		Course course_to_delete = (((Boom*)DS)->courses_hash).find(tmp1);// course to delete
		for (int i = 0; i < ((((Boom*)DS)->courses_hash).find(tmp1)).classes_array->curr_num; i++)//remove from the classes tree
		{
			Class tmp2(i, 0, course_to_delete.course_id);
			Class class_to_delete = ((((Boom*)DS)->courses_hash).find(tmp1)).classes_array->find(tmp2);// course to delete
			AVLNode<Class>* tmpcl = (((Boom*)DS)->classes_tree).find(((((Boom*)DS)->classes_tree).getRoot()), class_to_delete);
			if (tmpcl)//look if the class exists in the classes tree if not null will be returned
			{//the class exists in the tree therefore we call a function to remove it
				(((Boom*)DS)->classes_tree).remove(tmpcl->getValue());
			}
		}//after deleting all the class of the courese from the courses tree it is safe to delete the course from the courses table
		(((Boom*)DS)->courses_hash).deleteElem(course_to_delete);
		return SUCCESS;
	}
	catch (Course::ALLOC_ERROR())
	{
		return ALLOCATION_ERROR;
	}
	catch (RankTree<Course>::NOT_EXIST())
	{
		return FAILURE;
	}
	catch (RankTree<Class>::NOT_EXIST())
	{
		return FAILURE;
	}
	catch (...)
	{
		return FAILURE;
	}
	return SUCCESS;
}
//assigning new class to a course, inserting the class to the (course->clasess hash table)
//O(1) on avarge,insert to an hash table is O(1) on avarge.
StatusType AddClass(void* DS, int courseID, int* classID)
{
	if (courseID <= 0 || DS == NULL)
	{
		return INVALID_INPUT;
	}
	try
	{
		Course tmp1(courseID);
		Course course_to_add_to = (((Boom*)DS)->courses_hash).find(tmp1);//// the course we would like to add the class to 
		//the class id is determined by number of the existing classes in the course
		int class_id_new = ((((Boom*)DS)->courses_hash).find(tmp1)).classes_array->curr_num;
		Class new_class(class_id_new, 0, courseID);//creates an instance of class with the new id ,zero views and the given course id 
		//(finds the course in the courses table by the course id and insert it to the class table of the course by the class id )
		(((Boom*)DS)->courses_hash).find(tmp1).classes_array->insertElem(new_class);
		*classID = class_id_new;
		return SUCCESS;
	}
	catch (Course::ALLOC_ERROR())
	{
		return ALLOCATION_ERROR;
	}
	catch (RankTree<Course>::NOT_EXIST())
	{
		return FAILURE;
	}
	catch (RankTree<Class>::NOT_EXIST())
	{
		return FAILURE;
	}
	catch (...)
	{
		return FAILURE;
	}
	return SUCCESS;
}
//watching a certin class, finds the wanted class from the 2 hashing tables, then if this is the first 
//watch so just adding the class to the watch_classes_tree else, removing the class for the updating the time
//and add the updated class to the tree
//O(LogM) on avarge, find/insert in hash table is O(1) on avarge, remove/insert/find from AVL is logM

//print's the current classes in order(from smallest to biggest)
void Print(void* DS)
{
	(((Boom*)DS)->courses_hash).print();
	std::cout << "\n"; std::cout << "\n"; std::cout << "\n";
	(((Boom*)DS)->classes_tree).printInOrder((((Boom*)DS)->classes_tree).getRoot());
	std::cout << "\n";
}

StatusType WatchClass(void* DS, int courseID, int classID, int time)
{
	if (time <= 0 || DS == NULL || courseID <= 0 || classID < 0)
	{
		return INVALID_INPUT;
	}
	try
	{
		Course tmp1(courseID);
		Course course_to_watch = (((Boom*)DS)->courses_hash).find(tmp1);// course to delete
		int num_of_classes = (((Boom*)DS)->courses_hash).find(tmp1).classes_array->curr_num;
		if (classID + 1 > num_of_classes)
		{
			return INVALID_INPUT;
		}
		Class tmp2(classID, 0, courseID);
		Class class_to_watch = ((((Boom*)DS)->courses_hash).find(tmp1).classes_array)->find(tmp2);//
		if (class_to_watch.time_watched == 0)//first watch
		{
			Class temp_class(classID, time, courseID);
			(((Boom*)DS)->classes_tree).insert(temp_class);
			((((Boom*)DS)->courses_hash).find(tmp1)).classes_array->find(temp_class).SetTime(time);
			return SUCCESS;
		}//already watched
		if ((((Boom*)DS)->classes_tree).find((((Boom*)DS)->classes_tree).getRoot(), class_to_watch) != NULL)//find it in the tree and remove it if exists
			(((Boom*)DS)->classes_tree).remove(class_to_watch);
		int new_time = class_to_watch.time_watched + time;
		(((Boom*)DS)->classes_tree).insert(Class(classID, new_time, courseID));//adds it to the tree 
		((((Boom*)DS)->courses_hash).find(tmp1).classes_array->find(class_to_watch)).time_watched += time;//updates the time in the hash table 
		return SUCCESS;
	}
	catch (RankTree<Course>::ALLOC_ERROR())
	{
		return ALLOCATION_ERROR;
	}
	catch (Course::ALLOC_ERROR())
	{
		return ALLOCATION_ERROR;
	}
	catch (RankTree<Course>::NOT_EXIST())
	{
		return FAILURE;
	}
	catch (...)
	{
		return FAILURE;
	}
	return SUCCESS;
}
//returns the time watched of a certain class, find the class from the 2 tables
//O(1) on avarge, just find on hash
StatusType TimeViewed(void* DS, int courseID, int classID, int* timeViewed)
{
	if (((Boom*)DS) == NULL || courseID <= 0 || classID < 0)
	{
		return INVALID_INPUT;
	}
	try
	{
		Course tmp1(courseID);
		int num_of_classes = (((Boom*)DS)->courses_hash).find(tmp1).classes_array->curr_num;
		//, because we dont remove classes the id of the classes is from 0 to the number of the class -1
		if (classID + 1 > num_of_classes)
			return INVALID_INPUT;
		Course course_time = (((Boom*)DS)->courses_hash).find(tmp1);// course to delete
		Class tmp2(classID, 0, courseID);//lookup is done only by the class id inside of a course classes hash table
		Class class_time = ((((Boom*)DS)->courses_hash).find(tmp1).classes_array)->find(tmp2);// course to delete
		(*timeViewed) = class_time.time_watched;
		return SUCCESS;
	}
	catch (RankTree<Course>::ALLOC_ERROR())
	{
		return ALLOCATION_ERROR;
	}
	catch (Course::ALLOC_ERROR())
	{
		return ALLOCATION_ERROR;
	}
	catch (RankTree<Course>::NOT_EXIST())
	{
		return FAILURE;
	}
	catch (...)
	{
		return FAILURE;
	}
	return SUCCESS;
}
//returns the index of a certain class, uses the Rank Tree.
//Log(M) just select in a rank Tree.
StatusType GetIthWatchedClass(void* DS, int i, int* courseID, int* classID)
{
	if (i <= 0 || DS == NULL)
		return INVALID_INPUT;
	try {
		Class class_return = (((Boom*)DS)->classes_tree).select(i);
		*courseID = class_return.course_id;
		*classID = class_return.class_id;
		return SUCCESS;
	}
	catch (RankTree<Course>::ALLOC_ERROR())
	{
		return ALLOCATION_ERROR;
	}
	catch (Course::ALLOC_ERROR())
	{
		return ALLOCATION_ERROR;
	}
	catch (RankTree<Course>::NOT_EXIST())
	{
		return FAILURE;
	}
	catch (...)
	{
		return FAILURE;
	}
	return SUCCESS;
}
//run's through all the tree's and deleting every node
//complexity: o(n+m) as n is the of courses and m is the nnumber of classes
void Quit(void** DS)
{
	(((Boom*)(*DS))->classes_tree).deleteAVLNode((((Boom*)(*DS))->classes_tree).getRoot()); //(num of classes in DS)
	*(DS) = NULL;
	(DS) = NULL;
}
