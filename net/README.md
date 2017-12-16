# Arctic Fox Networking Protocol - AFNP
This protocol will try to bridge the gap between some of the well defined protocols such as NETCONF, gRPC, SNMP, JSON,
XML, YANG, etc.  The goal of this protocol is to provide a protocol that is:
* Fast
* Easy to use
* Has a well defined schema (Such as JSON, XML, or YANG)
* Can be secured (encrypted)
* Has reliable (slow) and unreliable (fast) transports

This is an experiment to see if I can make an interesting protocol using the best of both worlds (maybe).  The idea is that you update items in your database and these items will be sent by the ANFP stack at every interval (unless specified otherwise) and will be sent immediately upon receipt.

## The Reliable (Slow) Transport
This is a TCP transport that carries the slow connection information.

This is used as the initial setup connection.

## The Unreliable (Fast) Transport

## The Arctic Fox Modeling Language - AFML
### The syntax is as follows
The syntax of this file follows a parameter-name PARAMETER-VALUE {} syntax.

| Parameter Value   | Parameter Value Description                                                                     |
| ----------------- | ----------------------------------------------------------------------------------------------- |
| MODULE NAME       | The name of the module.  Must match the filename, (e.g. A module named "demo-module.afml")      |
| MODULE MODE       | The mode of the module.  Module modes can have the following values                             |
| MODULE-MODE-VALUE | HANDOFF - Starts a TCP connection that hands off the connection UDP port trading                |
|                   | NORMAL - Starts a TCP connection that spawns off UDP connections and keeps both                 |

There are only a few primitive types:
* number - A number that can be expressed in the same way a Number is defined in https://tools.ietf.org/html/rfc7159
* string - A String of zero or more characters
* binary - A blob of binary data
* map - A map of data that can contain one or more keys

EXTRA-INFO - This can be used for the following information
* description - Description of the immediate parent surrounded in quotes.
* reliable - a value of "true" means everything in the immediate container and its children will be sent on the reliable channel
* global-update-interval - the global update interval where all data will be sent if available 
* update-interval - the update interval of everything in the immediate parent container
* must-update-time - the maximum time this entry will be sent before an update occurs
* tag - additional tag information

```
# Comment
module-name MODULE-NAME {
  module-mode MODULE-MODE {
    MODULE-MODE-VALUE
  }
  security SECURITY-MODE;
  data-unit UNIT-NAME {
    EXTRA-INFO;
    number[size] NUMBER-NAME {
      EXTRA-INFO;
    }
    string[size] STRING-NAME {
      EXTRA-INFO;
    }
    binary[size] BINARY-NAME {
      EXTRA-INFO;
    }
    map MAP-NAME {
      key [KEY, LIST];
      KEY_TYPE[size] KEY {
        EXTRA-INFO;
      }
      KEY_TYPE[size] LIST {
        EXTRA-INFO;
      }
    }
  }
}
```

### Other notes:

Multi-line quotes are acceptable:
```
"This is some text"
"This is more text"
"This is the last line of text";  # Note the ending ;
```
