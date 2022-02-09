
#include "../include/custom_id.h"

#include <cassert>

int main(int argc, char **argv) {

    CustomId cid;

    assert(!cid.setCurrentId("D1"));

    assert(cid.nextId() == "A1");

    assert(cid.nextId() == "A2");
   
    assert(cid.setCurrentId("A9"));
    assert(cid.nextId() == "B1");

    assert(cid.setCurrentId("Z9"));
    assert(cid.nextId() == "A1-A1");

    assert(cid.nextId() == "A1-A2");

    assert(cid.setCurrentId("A1-Z9"));
    assert(cid.nextId() == "A2-A1");

    assert(cid.nextId() == "A2-A2");
    
    assert(cid.setCurrentId("A2-Z9"));
    assert(cid.nextId() == "A3-A1");

    assert(cid.setCurrentId("Z9-Z9"));
    assert(cid.nextId() == "A1-A1-A1");

    assert(cid.setCurrentId("A1-A1-Z9"));
    assert(cid.nextId() == "A1-A2-A1");

    assert(cid.setCurrentId("A1-Z9-Z9"));
    assert(cid.nextId() == "A2-A1-A1");

    assert(cid.setCurrentId("Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9"));
    assert(cid.nextId() == "A1");
        
    assert(!cid.setCurrentId("Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9"));
}