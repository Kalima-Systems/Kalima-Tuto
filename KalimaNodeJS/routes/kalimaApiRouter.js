var express = require("express");
var router = express.Router();
var kalimaApi = require("../libs/kalima/kalimaApi");
var kalimaEventsApi = require("../libs/kalima/kalimaEventsApi");

kalimaApi.init(process.env.FILES_PATH);
kalimaEventsApi.init(process.env.FILES_PATH);

router.get("/events", function (req, res) {
  kalimaEventsApi.addClient(req, res);
});

router.get("/*", function (req, res) {
  kalimaApi.get(req, res);
});

router.delete("/*", function (req, res) {
  kalimaApi.delete(req, res);
});

router.post("/*", function (req, res) {
  kalimaApi.post(req, res);
});

module.exports = router;
