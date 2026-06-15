const METHOD = 'POST';
const HOST = 'mister';
const PORT = '8182';
const ENDPOINT = '/controls/keyboard/screenshot';
const URL = 'http://' + HOST + ':' + PORT + '/api' + ENDPOINT;

Pebble.addEventListener('ready', function() {
  console.log('PebbleKit JS ready!');
  
  // Update s_js_ready on watch
  Pebble.sendAppMessage({'JSReady': 1});
});

// Get AppMessage events
Pebble.addEventListener('appmessage', function(e) {
  const dict = e.payload;

  console.log('Got message: ' + JSON.stringify(dict));
  
  var request = new XMLHttpRequest();
  request.onload = function() {
    console.log('Got response: ' + this.responseText);
    
    Pebble.sendAppMessage({'Done': 1});
  };
  
  console.log('Sending ' + METHOD + ' request to ' + URL);
  request.open(METHOD, URL);
  request.send();
  
});