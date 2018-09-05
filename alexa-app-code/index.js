var alexa = require('alexa-app');
var Particle = require('particle-api-js');

// Allow this module to be reloaded by hotswap when changed
module.change_code = 1;

// Define an alexa-app
var app = new alexa.app('ceiling-fan-remote');
app.id = require('./package.json').alexa.applicationId;

const DEVICE_ID = "YOUR_DEVICE_ID";
const TOKEN_ID = "YOUR_PARTICLE_ACCESS_TOKEN";

const MSG_HELP = "Vous devez spécifier une commande, comme lumière, variateur ou vitesse de 0 à 3. Par exemple, Alexa, demande au ventilateur de changer la lumière, ou Alexa, demande au ventilateur de mettre la vitesse 3";
const MSG_PARTICLE_ERROR = "Une erreur s'est produite, veuillez recommencer ultérieurement";

const MSG_SPEED_NONE = "La vitesse doit être comprise entre 0 et 3.";
const MSG_SPEED_0 = "C'est fait, ventilateur arrêté.";
const MSG_SPEED_1 = "C'est fait, vitesse 1.";
const MSG_SPEED_2 = "C'est fait, vitesse 2.";
const MSG_SPEED_3 = "C'est fait, vitesse 3.";

const MSG_DONE = "C'est fait.";

var particle = new Particle();

app.pre = function(request, response, type) {
  console.log(request.type())
}

app.launch(function(req, res) {
  res.say(MSG_HELP);
});

app.intent('SetSpeedIntent', {
  "slots": {"speed" : "AMAZON.NUMBER"},
  "utterances": ["vitesse speed"]
}, function(req, res) {
  var speed = req.slot('speed');

  if (speed > 3 || !speed || speed == '?') {
    res.say(MSG_SPEED_NONE);

  } else if (speed == 0) {
    var fnPr = particle.callFunction({ deviceId: DEVICE_ID, name: 'cmdSpeed0', argument: '', auth: TOKEN_ID });
    fnPr.then(
      function(data) {
        res.say(MSG_SPEED_0)
      }, function(err) {
        console.log('An error occurred:', err);
        res.say(MSG_PARTICLE_ERROR);
    });

    return fnPr;

  } else if (speed == 1) {
    var fnPr = particle.callFunction({ deviceId: DEVICE_ID, name: 'cmdSpeed1', argument: '', auth: TOKEN_ID });
    fnPr.then(
      function(data) {
        res.say(MSG_SPEED_1)
      }, function(err) {
        console.log('An error occurred:', err);
        res.say(MSG_PARTICLE_ERROR);
    });

    return fnPr;

  } else if (speed == 2) {
    var fnPr = particle.callFunction({ deviceId: DEVICE_ID, name: 'cmdSpeed2', argument: '', auth: TOKEN_ID });
    fnPr.then(
      function(data) {
        res.say(MSG_SPEED_2)
      }, function(err) {
        console.log('An error occurred:', err);
        res.say(MSG_PARTICLE_ERROR);
    });

    return fnPr;

  } else if (speed == 3) {
    var fnPr = particle.callFunction({ deviceId: DEVICE_ID, name: 'cmdSpeed3', argument: '', auth: TOKEN_ID });
    fnPr.then(
      function(data) {
        res.say(MSG_SPEED_3)
      }, function(err) {
        console.log('An error occurred:', err);
        res.say(MSG_PARTICLE_ERROR);
    });

    return fnPr;

  }
});

app.intent('SetLightIntent', {
  "slots": {},
  "utterances": ["lumière"]
}, function(req, res) {
  var fnPr = particle.callFunction({ deviceId: DEVICE_ID, name: 'cmdOnOff', argument: '', auth: TOKEN_ID });

  fnPr.then(
      function(data) {
        res.say(MSG_DONE)
      }, function(err) {
        console.log('An error occurred:', err);
        res.say(MSG_PARTICLE_ERROR);
    });

    return fnPr;

});

app.intent('SetDimmerIntent', {
  "slots": {},
  "utterances": ["variateur"]
}, function(req, res) {
  var fnPr = particle.callFunction({ deviceId: DEVICE_ID, name: 'cmdDimmer', argument: '', auth: TOKEN_ID });

  fnPr.then(
      function(data) {
        res.say(MSG_DONE)
      }, function(err) {
        console.log('An error occurred:', err);
        res.say(MSG_PARTICLE_ERROR);
    });

    return fnPr;

});

module.exports = app;
