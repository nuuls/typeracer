// paste this in the console on typeracer if the counter is at 1 or lower and click the type field
var postData = $(".nonHideableWords").innerHTML;
var async = true;
var request = new XMLHttpRequest();
request.open("POST", "http://localhost:8181", async);
request.send(postData);

//$(".textInfoOwnStatsNumber").title
