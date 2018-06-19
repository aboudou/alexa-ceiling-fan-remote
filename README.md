Description
==
Alexa ceiling fan remote allows you to control an SM5021 (emitter) / SM5032 (receiver) based infrared remote.

I named it "ceiling fan remote" because I made it to replace the IR remote of my ceiling fan.


You will need :
* A Particle device (tested with Core, should work with others)
* An IR LED
* A NPN transistor (BC547 here)
* A 100 ohms resistor
* A 220 ohms resistor


Notes
==

The code is made for french version of Alexa. You may have to change some files to adapt to your langage.

The "dimmer" function does nothing. It send the correct sequence (according to SM5021 datasheets), but there's no result. I suspect an error with the datasheet, I need to check it with an oscilloscope.


Video
==

https://www.youtube.com/watch?v=ZA8zbPqXQsI


Project structure
==

alexa-app-code
===

This is the application code to use on your own server with alexa-js-app-server (https://github.com/alexa-js/alexa-app-server).

Copy the files into “/path/to/alexa-js-app-server/apps/the-name-you-want”.

Then install particle-js node module from the above path :
> npm install particle-api-js

You may want to modify these files :
* index.js :
  * DEVICE_ID : the device id of your particle device. You may get it at https://console.particle.io/
  * TOKEN_ID : your access token to Particle API. See https://docs.particle.io/reference/api/#generate-an-access-token
  * All MSG_xxx constants to adapt to your language.
* package.json
  * applicationId : the applicationId for your Alexa skill. Get if from https://developer.amazon.com/alexa/console/ask


alexa-skill-json
==

The json code to use when creating your alexa skill. You may to change “invocationName” and “samples” keys to adapt to your language.

The endpoint is the URL where your alexa-app-code is hosted.

particle-core-code
==

The code to flash to your Particle device. Tested with Particle Core, should work with others (Photon, Electron, etc.)

The IR code comes from https://github.com/qwertzguy/Spark-Core-IRremote

docs
==

* schematics.jpg : how to connect nuts and bolts
