# c-32bit-to-64bit-porting-issues

## Description
32-bit->64-bit Porting Guide Document:

## 64-bit Applications:
64-bit programs use aproximately 30% to 40% more memory then their 32-bit counterparts
### Advantages
1. Large file caches on systems with large physical memory
2. Large process data space mapped in a large virtual address space
3. Large file support using standard system library calls
4. Processor has more registers, so it doesn't need to access memory that often.
5. Calculations (64-bit numbers etc.) are more efficient.

### Disadvantages
1. less code/data can fit into processor caches
    * more cache misses
        * Processor waits more for memory controller to fetch data from RAM.
		* Processor also needs to read more data because it's more bloated.
2. Less free memory available
    * less space for disk caches
    * slower disk access
3. Once we are out of RAM and the system starts swapping
    * disk access is thousands times slower than RAM, so any potential benefits of 64-bit code are counteracted.
### Conclusion
Basically, it's like giving up 30% of RAM in exchange of possible gain of 10% CPU speed.

## Data Models:
|Datatype    |  ILP32  |   LP64  |
|------------|---------|---------|
|char        |  8      |   8     |
|short       |  16     |   16    |
|int         |  32     |   32    |
|long        |  32     |   64    |
|pointer     |  32     |   64    |
|long long   |  64     |   64    | 
|float       |  32     |   32    |
|double      |  64     |   64    |
|long double |  128    |   128   |
|enum        |  32     |   32    |

## Common Issues
* Data truncation
* Pointers
* Data type promotion
* Data alignment and data sharing
* Constants
* Bit shifts and bit masks
* Bit fields
* Enumerated types

### Data Truncation
pointers, long, off_t, fpos_t etc are all 64bit in LP64 data model.
In LP64, truncation can occur during, initialization, assignments, parameter passing, return statements and casting.

* Assigning longs to ints
* Storing long int in double
* Storing Pointers in ints or ints/hexadecimal literal to a pointer
* Truncating Function Return Values
* Not using appropriate Print Specifiers
### Pointers:
* Pointer Arithmetic between longs and ints
### Data Type Promotion:
* Expression leading to Sign Extension scenarios
* Arithmetic between signed and unsigned numbers
### Data alignment and data sharing (Structures & Unions):
* The compilers align data types on a natural boundary.
  Structure or a Union will be different on 32-bit and 64-bit systems.
* look out for struct member offsets and thier alignment
* give extra care when union's uses pointers and primitive datatypes

### Constants:
The datatype of hexadecimal constants may changes between ILP32 and LP64,

| Constants   | ILP32         | LP64         |
|-------------|---------------|--------------|
| 0x7fffffff  | int           | int          |
| 0x7fffffffL | long          | long         |
| 0x80000000  | unsigned int  | unsigned int |
| 0x80000000L | unsigned long | long         |

* Using Literals and Masks that Assume 32 bits
* Using mixed datatypes
* Hardcoding Size of Data Types
* Hardcoding Constants with malloc(), memory(), string()
* Hardcoding Bit Shift Values

### Bit Fields:
* Sign extension in bit fields

### Enumerated Types:
* In LP64, enumerated types are signed only if one or more of the
  enumeration constants defined for that type is negative. If all
  enumeration constants are non-negative, the type is unsigned. In ILP32,
  enumerated types are always signed.

### Endianess:
* little endian - ll (l - least significant bytes, l - lowest memory address)
* bit endian    - ml (m - most significant bytes, l - lowest memory address) (network order)
**Endianism is important when**
* Bit masks are used
* Indirect pointers address portions of an object
## Performance Considerations:
* long division is more time-consuming than 32-bit integer division
* 64-bit programs that use 32-bit signed integers as array indexes
  require additional instructions to perform sign extension each time
