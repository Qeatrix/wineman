# wineman

Wineman is a utility for quick access and management of wine prefixes

## Warning
Basic functionality is still under development

## Todo
- [ ] Handle cd into prefixes root folder
- [ ] Silent create a prefix when creating a new json entry
- [ ] Creating a new data.json file if it does not exist
- [ ] Interaction with environment variables
- [ ] Config file support
- [ ] Using a dedicated directory for a data file

## Compile
1. Clone and get into repository
```bash
git clone https://github.com/unxsh/wineman.git && cd wineman
```

2. Create build folder and get into it
```bash
mkdir build && cd build
```

3. Compile the app
```bash
cmake .. && make
```

4. Run the app
```bash
./wineman
```

## Install
```bash
sudo cp wineman /usr/local/bin
```
