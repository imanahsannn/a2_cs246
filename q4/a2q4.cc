#include <iostream>
#include <sstream>
using namespace std;
const int MAX_INT_SETS = 5;

struct IntSet {
  int *data;
  int size;
  int capacity;
};

void init( IntSet & i );    // Initialize to be "empty" with following field values: {nullptr,0,0}
void destroy( IntSet & i ); // Clean up the IntSet and free dynamically allocated memory.

IntSet operator| ( const IntSet & i1, const IntSet & i2 ); // Set union.
IntSet operator& ( const IntSet & i1, const IntSet & i2 ); // Set intersection.
bool   operator==( const IntSet & i1, const IntSet & i2 ); // Set equality.

bool isSubset( const IntSet & i1, const IntSet & i2 );   // True if i2 is a subset of i1.
bool contains( const IntSet & i, int e );                // True if set i contains element e.
void add( IntSet & i, int e );                           // Add element e to the set i.
void remove( IntSet & i, int e );                        // Remove element e from the set i.

// Output operator for IntSet.
std::ostream& operator<<( std::ostream & out, const IntSet & is );

// Input operator for IntSet. Continuously read int values from in and add to the passed IntSet.
// Function stops when input contains a non-int value. Discards the first non-int character.
std::istream& operator>>( std::istream & in, IntSet & is );


// Test harness for IntSet functions. You may assume that all commands entered are valid.
// Valid commands: n <ind>,  p <ind>, & <ind1> <ind2>,
//                 | <ind1> <ind2>, = <ind1> <ind2>,
//                 s <ind1> <ind2>, c <ind1> <elem>,
//                 a <ind1> <elem>, r <ind1> <elem>,
//                 q/EOF
// Silently ignores invalid commands. Doesn't check that 0 <= index < MAX_INT_SETS.
// Do not test invalid commands!

int main() { 
  bool done = false;
  IntSet sets[MAX_INT_SETS], tmpSet;
  for ( int i = 0; i < MAX_INT_SETS; i++ ) init( sets[i] );
  init( tmpSet );

  while ( ! done ) {
    char c;
    int lhs, rhs;
    cerr << "command?" << endl;
    cin >> c; // Reads command.

    if (cin.eof()) break;
 
    switch(c) {
      case 'n':
        // Create new IntSet at index lhs after destroying the old.
        // Read in integers to add to it until hitting non int using operator>>.
        cin >> lhs;
        destroy( sets[lhs] );
        init( sets[lhs] );
        cerr << "enter integer values for sets[" << lhs << "], terminated by non-int: " << endl;
        cin >> sets[lhs];
        break;

      case 'p':
        // Print IntSet at lhs.
        cin >> lhs;
        cout << sets[lhs] << endl;
        break;

      case '&':
        // Print intersection of lhs and rhs.
        cin >> lhs >> rhs; // reads in two indices
        destroy( tmpSet );
        init( tmpSet );
        tmpSet = (sets[lhs] & sets[rhs]);
        cout << tmpSet << endl;
        break;

      case '|':
        // Print union of lhs and rhs.
        cin >> lhs >> rhs;
        destroy( tmpSet );
        init( tmpSet );
        tmpSet = (sets[lhs] | sets[rhs]);
        cout << tmpSet << endl;
        break;

      case '=':
        // Print true if lhs == rhs, false otherwise.
        cin >> lhs >> rhs;
        cout << boolalpha << (sets[lhs] == sets[rhs]) << endl;
        break;

      case 's':
        // Print true if rhs is subset of lhs, false otherwise.
        cin >> lhs >> rhs;
        cout << boolalpha << isSubset( sets[lhs], sets[rhs] ) << endl;
        break;

      case 'c':
        // Print true if lhs contains element rhs, false otherwise.
        cin >> lhs >> rhs;
        cout << boolalpha << contains( sets[lhs], rhs ) << endl;
        break;

      case 'a':
        // Add elem rhs to set lhs
        cin >> lhs >> rhs;
        add( sets[lhs], rhs );
        break;

      case 'r':
        // Remove elem rhs from set lhs
        cin >> lhs >> rhs;
        remove( sets[lhs], rhs );
        break;
        
      case 'q':
        // Quit
        done = true;
        break;

    } // switch
  } // while

  for ( int i = 0; i < MAX_INT_SETS; i++ ) destroy( sets[i] );
  destroy( tmpSet );
} // main
