#ifndef HW1_EXCEPTION_H
#define HW1_EXCEPTION_H
#include <exception>
/*
* Class NodeNotFound : std::exception
* This class represents an exception thrown when a requested node is not found.
*/
class NodeNotFound : public std::exception {

    /*
    * Provide information regarding the error - the node that was searched was not found.
    * @param - none
    * @return - const char* - description of exception
    */
    const char* what() const noexcept override
    {
        return "Node Not Found Error: The following node does not exist in the tree";
    }

};
class EmptyTree : public std::exception {

    /*
    * Provide information regarding the error - the node that was searched was not found.
    * @param - none
    * @return - const char* - description of exception
    */
    const char* what() const noexcept override
    {
        return "Empty Tree Error: The tree is empty";
    }

};
class BadAllocation : public std::exception {

    /*
    * Provide information regarding the error - the node that was searched was not found.
    * @param - none
    * @return - const char* - description of exception
    */
    const char* what() const noexcept override
    {
        return "Bad allocation error: couldn't allocate";
    }

};

#endif