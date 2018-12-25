
///
/// @file Dependency.hpp
/// @brief TODO: Add file description
/// @author Matthew Baum
/// @copyright (c) 2018 Baum Network. All rights reserved.
///

#pragma once


#include <iostream>
#include <set>
#include <list>
#include <string>

// TODO: Fix to a correct dependency checker

/*
 * TODO: Turn into a needs API
 * Instead of nodeA.addChild(&nodeB); it should be
 * nodeB.needs(nodeA);
 *
 * Maybe this is a hierarchary loop checker as is and what I want is a dependency resolver?  Are they the same thing but reversed?
 * Too sleepy to think about this now.......zzzzzz
 */

namespace Dependency {
    enum class Status {
        ChildExists,
        Ok,
    };

    template<typename Type>
    class DNode {
    private:
        using DNodes = std::set<DNode<Type> *>;
        DNodes _nodes, _resolved, _unresolved;
        Type _type; // Actual data to hold

    protected:
        Status resolve(DNodes & resolved, DNodes & unresolved) {
            // Add ourselves to the unresolved list
            unresolved.insert(this);
            Status status;
            for (DNode<Type> * node : _nodes) {
                // If the node is not in the resolved list
                if (resolved.find(node) == resolved.end()) {
                    // If the node is in the unresolved list, then the child exists
                    if (unresolved.find(node) != unresolved.end()) {
                        return Status::ChildExists;
                    }
                    if ((status = node->resolve(resolved, unresolved)) != Status::Ok) { // Resolve the nodes
                        // TODO: one day can return the position
                        return status; // Prop the bad status up
                    }
                }
            }

            resolved.insert(this);
            unresolved.erase(unresolved.find(this));

            return Status::Ok;
        }

    public:
        DNode(Type type) : _type(type) {}

        Status addChild(DNode * node) {
            if (_nodes.find(node) != _nodes.end()) {
                return Status::ChildExists;
            }
            _nodes.insert(node);

            return Status::Ok;
        }

        void clear() {
            _nodes.clear();
        }

        Status resolve() {
            // Clear the lists
            _resolved.clear();
            _unresolved.clear();

            // Resolve the nodes
            return resolve(_resolved, _unresolved);
        }

        // Return the base data
        Type getType() const {
            return _type;
        }

        // Get a resolved list
        std::list<Type> getResolved() {
            std::list<Type> resolved;
            // List is usually the reverse of what is expected, reorder.
            for (auto & item = _resolved.rbegin(); item != _resolved.rend(); std::advance(item, 1)) {
                resolved.push_back((*item)->getType());
            }
            return resolved;
        }
    };

    template<typename Type>
    bool operator<(const DNode<Type> & lhs, const DNode<Type> & rhs) {
        return lhs.getType() < rhs.getType();
    }

    template<typename Type>
    void printResolved(DNode<Type> & root) {
        std::list<std::string> results = root.getResolved();
        for (auto & item : results) {
            std::cout << item << std::endl;
        }
    }
}

#if 0
#include <iostream>
#include <thread>
#include <chrono>
#include "Dependency.h"

int main() {
   Dependency::DNode<std::string> A(std::string{ "A" });
   Dependency::DNode<std::string> B(std::string{ "B" });
   Dependency::DNode<std::string> C(std::string{ "C" });
   Dependency::DNode<std::string> D(std::string{ "D" });

   std::cout << "This should not work:" << std::endl;

   A.addChild(&B);
   A.addChild(&C);
   A.addChild(&D);

   B.addChild(&C);
   C.addChild(&B);

   if (A.resolve() == Dependency::Status::Ok) {
      std::cout << "We should not be here - printing the tree." << std::endl;
      Dependency::printResolved(A);
   }
   else {
      std::cout << "Correctly does not print the tree." << std::endl;
   }

   std::cout << "This should work:" << std::endl;

   A.clear();
   B.clear();
   C.clear();
   D.clear();

   A.addChild(&B);
   A.addChild(&C);
   A.addChild(&D);

   B.addChild(&D);

   C.addChild(&D);

   if (A.resolve() == Dependency::Status::Ok) {
      std::cout << "Correctly prints the tree." << std::endl;
      Dependency::printResolved(A);
   }
   else {
      std::cout << "We should not be here - did not print the tree." << std::endl;
   }

   std::this_thread::sleep_for(std::chrono::seconds(10));

   return 0;
}

#endif