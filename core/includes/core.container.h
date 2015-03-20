#pragma once

#include <core/container/Operations.h>
#include <core/container/Operators.h>
#include <core/container/Enumerable.h>
#include <core/container/Array.h>
#include <core/container/LinkedList.h>
#include <core/container/Set.h>

//specialization
#include <core/container/operations/specialization/array.h>  //this takes long to compile.... maybe it should not be on by default
#include <core/container/operations/specialization/stdcontainer.h>
#include <core/container/operations/specialization/dslib.h>
#include <core/container/operations/specialization/linkedlist/Enumerator.h>
#include <core/container/operations/specialization/linkedlist/AddItem.h>
#include <core/container/operations/specialization/linkedlist/RemoveItem.h>
