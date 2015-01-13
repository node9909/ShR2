<html>
<head>
<title>ESP8266 - esphttpd</title>
<!-- Bootstrap Core CSS -->
<link rel="stylesheet" type="text/css" href="static/css/bootstrap.min.css">
<!-- Custom CSS -->
<style>
body {
padding-top: 70px;
/* Required padding for .navbar-fixed-top. Remove if using .navbar-static-top. Change if height of navigation changes. */
}
</style>
<!-- HTML5 Shim and Respond.js IE8 support of HTML5 elements and media queries -->
<!-- WARNING: Respond.js doesn't work if you view the page via file:// -->
<!--[if lt IE 9]>
<script src="https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js"></script>
<script src="https://oss.maxcdn.com/libs/respond.js/1.4.2/respond.min.js"></script>
<![endif]-->
<!-- jQuery Version 1.11.1 -->
<script src="/static/js/jquery.min.js"></script>
<script src="/static/js/jquery.pjax.min.js"></script>
<script src="/static/js/scan_aps.js"></script>
<script src="/static/js/140medley.min.js"></script>
<script>
$(function(){
	$("#navbar").load("/navbar.html");
});
</script>
<script>
$(document).pjax('a[data-pjax]', 'pjax-container');
$(document).on('pjax:success', function() {
	scanAPs();
})
</script>
</head>
<body>
<div id="navbar"></div>
<!-- Page Content -->
<div class="container" id="pjax-container">
<div class="row">
<div class="col-lg-12 text-center">
<h1>It works</h1>
<p class="lead">If you see this, it means the tiny li'l website in your ESP8266 does actually work. Fyi, this page has
been loaded <b>%counter%</b> times.</p>
<ul class="list-unstyled">
<li>If you haven't connected this device to your WLAN network now, you can <a data-pjax href="/wifi">do so.</a></li>
<li>You can also control the <a data-pjax href="led.tpl">LED</a>.</li>
<li>You can download the raw <a href="flash.bin">contents</a> of the SPI flash rom</li>
</ul>
</div>
</div>
<!-- /.row -->
</div>
<!-- /.container -->
<!-- Bootstrap Core JavaScript -->
<script src="static/js/bootstrap.min.js"></script>
</body>
</html>
