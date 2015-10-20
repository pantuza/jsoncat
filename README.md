jsoncat
=======

### Description
Json pretty-print parser based on a recursive lexical analyser 

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

### Author

###### Written by [Gustavo Pantuza](https://pantuza.com)

### Reporting Bugs

###### Report Jsoncat bugs to gustavopantuza@gmail.com
