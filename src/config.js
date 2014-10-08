// Pebble.addEventListener("ready",
//   function(e) {
//     console.log("PebbleKit JS ready!");
//   }
// );

Pebble.addEventListener("showConfiguration", function (e) {
  //Load the remote config page
  var back_color = window.localStorage.getItem('back_color') === null ? 'black' : window.localStorage.getItem('back_color');
  var lang_formal = window.localStorage.getItem('lang_formal') === null ? 'casual' : window.localStorage.getItem('lang_formal');
  var from_time = window.localStorage.getItem('from_time') === null ? '8' : window.localStorage.getItem('from_time');
  var to_time = window.localStorage.getItem('to_time') === null ? '20' : window.localStorage.getItem('to_time');
  Pebble.openURL("http://panayotis.com/pebble/greekclockcfg.html?backcolor=" + back_color + "&language=" + lang_formal + "&from=" + from_time + "&to=" + to_time);
});

Pebble.addEventListener("webviewclosed", function (e) {
  //Get JSON dictionary
  var configuration = JSON.parse(decodeURIComponent(e.response));
  window.localStorage.setItem('back_color', configuration.background);
  window.localStorage.setItem('lang_formal', configuration.language);
  window.localStorage.setItem('from_time', configuration.from);
  window.localStorage.setItem('to_time', configuration.to);

  //Send to Pebble, persist there
  Pebble.sendAppMessage({
	  "KEY_BLACK": configuration.background,
	  "KEY_LANGFORMAL": configuration.language,
	  "KEY_FROM": configuration.from,
	  "KEY_TO": configuration.to
  },
  function (e) {
    console.log("Configs succeed");
  }, function (e) {
    console.log("Configs failed");
  });
  
});