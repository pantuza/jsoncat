Jsoncat
=======

### Description
Json pretty-print parser based on a recursive lexical analyser. 
The parser was based on the specification defined at [json.org](http://json.org).
The input file is parsed to build a json object.
If the object is correct, it will be pretty-printed to standard output.

### Usage
Jsoncat parses a json that comes from a pipe to stdin. For example, parsing a request:
```bash
$> curl -s https://pantuza.com/sample.json --insecure | bin/jsoncat
```
```javascript
{
        'what': "A json example file",
        'test': true,
        'values': [ 42, 10, 5.32],
        'data': {
                'name': 'Test Name',
                'type': null
        }
}
```

Or simple by passing a path to a json file as follows:
```bash
$> jsoncat tests/samples/input_06.json
```
```javascript
{
        'age': 42,
        'name': 'marvin',
        'what': 'robot'
}
```

Or yet, again from stdin, by echoing a json:
```bash
$> echo "{'test': true}" | jsoncat
```
```javascript
{
        'test': true
}
```

### Options
        
**-v | --version**
> Prints jsoncat version

**-h | --help**
> Prints help message

**--no-color**
> Does not prints json files using colors

### Contributing

See [here](https://github.com/pantuza/jsoncat/blob/master/CONTRIBUTING.md) how to contribute to **Jsoncat** project

### Author

###### Written by [Gustavo Pantuza](https://pantuza.com)

### Reporting Bugs

###### Report Jsoncat bugs to gustavopantuza@gmail.com
