#include "ID.h"
#include <iostream>
#include <sstream>


// ID with No Discriminator
// Here ID1 and ID2 are actually the same type, since 'using' creates an alias to another type.
// This means an instance of ID1 may be assigned to an instance of ID2 and more generally
// instances of both types may be freely mixed. This is usually not what we want.
// ID1 and ID2 provide a raw_value function since it is the only way to access the contained value.
using ID1 = ID<uint32_t>;
using ID2 = ID<uint32_t>;

// ID with Empty Discriminator
// Here Thing1ID is given a discriminator type that is the empty class Thing1.
// This means that Thing1ID is a different type than ID1 even though they both contain uint32_t's.
// Thing1ID has a raw_value function because it is an empty class. The raw_value function is
// needed to retrieve the contained value.
class Thing1 {};
using Thing1ID = ID<uint32_t, Thing1>;

// ID with Full Discriminator
// Here Thing2::ID is given a discriminator type that is the non-empty class Thing2. Thing2 is made
// a friend of Thing2::ID which allows Thing2 access to the raw value. Since the contained value is
// accessible to the friend no raw_value function is needed.
class Thing2 {
public:
    using ID = ::ID<uint32_t, Thing2>;

    static Thing2 retrieve(ID thing2_id) {
        Thing2 thing2;
        auto raw_id = thing2_id.id; // read access to id because Thing2 is a friend
        thing2.id_.id = raw_id;     // write access to id because Thing2 is a friend
        // ...
        return thing2;
    }

    std::string label() {
        std::ostringstream os;
        os << "This is instance " << id_ << " of class Thing2";
        return os.str();
    }

    // ...

private:
    ID id_;
    // ...
};

void usage_example() {
    ID1 id1{8735};
    ID2 id2{7263};
    id1 = id2; // OK: assignment available because Thing1ID has no discriminator
    uint32_t id1v = id1.raw_value(); // OK: raw_value available because Thing1ID has no discriminator
    std::cout << id1v << std::endl;

    Thing1ID t1id{2535};
    Thing2::ID t2id{90897};
    // t1id = t2id; // compiler error: they are different types since they have different discriminators
    uint32_t t1idv = t1id.raw_value(); // OK: raw_value available because Thing1ID has an empty discriminator
    std::cout << t1idv << std::endl;
    // uint32_t t2idv = t2id.raw_value(); // compiler error: Thing2::ID has a non-empty discriminator - thus no raw_value
    auto t2 = Thing2::retrieve(t2id);
    std::cout << t2.label() << std::endl;
}


int main() {
    usage_example();
    return 0;
}