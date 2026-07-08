#A simple Supermarket application for Cristie Digital.

Requires C++ 17 for std::optional, see build.sh.

Built on Ubuntu 24.0.4.4 LTS.

Json parsing header lib downloaded from https://github.com/nlohmann/json.

```
./build.sh
./checkout data.json
```

#Example:
```
./checkout data.json 
bread 1
banana 1
oatmeal 1
apple 4

Total : $ 2.25
```

