# Supermarket application for Christie Digital.

Requires C++ 17 for std::optional, see build.sh.

Built on Ubuntu 24.0.4.4 LTS.

Json parsing header lib downloaded from https://github.com/nlohmann/json.

## Build and Run
```
./build.sh
./checkout data.json
```

## Example
```
./checkout data.json 
bread 1
banana 1
oatmeal 1
apple 4

Total : $ 2.25
```

## Data File
The data.json file contains all the pricing rules and a list of items for the checkout. Data updates do not require recompilation. Since pricing information can change often I felt this was an appropriate architecure.

## TODO
- Unit tests
- More advanced build system

