# Log library
If you want to filter logs, you need to create a config file named:
`log.config`. And put that in the same level as your application. For example,
if your application is named `foo`, you have a directory structure such as:

```
$ ls -1
foo
log.config
```

Add properties in that file such as:
```
logging.level.<TAG>=<LEVEL>
```
`TAG` is a tag for the log created in your unit. So you can have multiple logs
in a single file or share the same log in multiple files just using a tag name.

You can control all logs using:
```
logging.level=<LEVEL>
```

## How to create a log
Including file is `log.h`.

```
Log *log = log_create("A_TAG");
```
Or if you want to bind the log to the file:
```
Log *log = log_create(__FILE__);
```
Print logs with:
```
log_debug(log, "debug log");
log_info(log,  "info log");
log_warn(log,  "warning log");
log_error(log, "error log");
```
