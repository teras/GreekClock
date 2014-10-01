// Pebble.addEventListener("ready",
//   function(e) {
//     console.log("PebbleKit JS ready!");
//   }
// );

Pebble.addEventListener("showConfiguration",
  function(e) {
    //Load the remote config page
    var back_color = window.localStorage.getItem('back_color');
    if (!back_color)
      back_color = "white";
    Pebble.openURL("http://panayotis.com/pebble/greekclockcfg.html?backcolor="+back_color);
  }
);

Pebble.addEventListener("webviewclosed",
  function(e) {
    //Get JSON dictionary
    var configuration = JSON.parse(decodeURIComponent(e.response));
    window.localStorage.setItem('back_color', configuration.background);
    
    //Send to Pebble, persist there
    Pebble.sendAppMessage(
      {"KEY_BLACK": configuration.background},
      function(e) {
        console.log("Sending settings data...");
      },
      function(e) {
        console.log("Settings feedback failed!");
      }
    );
  }
);