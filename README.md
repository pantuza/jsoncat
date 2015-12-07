Jsoncat
=======
![alt text][jsoncat_logo]
[jsoncat_logo]: https://github.com/pantuza/jsoncat/blob/master/img/jsoncat_logo.png "Jsoncat logo"

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

### Installation

###### From Homebrew for Mac OS
In a terminal install jsoncat from tap source:
```bash
$> brew tap pantuza/homebrew-jsoncat
$> brew install jsoncat
```

###### From source
Clone this repository, go to project directory and run:
```bash
$> make
$> make install
```
> **PS:** I'm creating the RPM and DEB packages. A soon as possible you would install jsoncat
> from these sources.

### Options
        
**-v | --version**
> Prints jsoncat version

**-h | --help**
> Prints help message

**--no-color**
> Removes the color characters. This characters are useful only for the terminal that will pretty print the Json.
> If you want to store the resulted Json to a file, use this option to persist a valid Json.

**--tab-stop**
> Sets the tab stop used by Jsoncat. We never insert tab character. Instead, we expand tab with spaces. 
> For that, the --tab-stop configures the number of spaces used for Json indentation. The default value
> is 4.

### Contributing

We are welcome to contributions. Just do a fork, modify some code and make a 
pull request. You may not forget to describe your modifications very well.
It will help us on the code review. Try to write some tests, it would be
nice.

### Coding style

we are not stringent with it, but we like the 
[GNU C coding 
style](https://www.gnu.org/prep/standards/html_node/Writing-C.html).

### Testing

Our test scripts are testing only the binary execution and checking for some
error during the parsing and at the result. 
We use bash scripts to do this task. 

At the tests directory, there is a utils.sh file that defines the tests functions.
Each other file in this directory uses the utils functions to run tests over 
strings, numbers, objects, arrays and constants. Also, there is a script to test
the command line options. The samples directory has a lot of json sample files
to use during development tests.

For now, we are not using any tool for testing :/. If you have suggestions 
for it, please put it in an issue, we will certain check it out. 


### Author

###### Written by [Gustavo Pantuza](https://pantuza.com)

### Reporting Bugs

###### Report Jsoncat bugs to gustavopantuza@gmail.com
