require("dotenv").config();

var express = require("express");
var bodyParser = require("body-parser");
fs = require("fs");
var path = require("path");
var kalimaApiRouter = require("./routes/kalimaApiRouter");
var app = express();

app.use(bodyParser.json());
app.use(express.json());
app.use(express.urlencoded({ extended: false }));

app.listen(process.env.PORT);
console.log(`app listening on port ${process.env.PORT}`);

app.use("/api", kalimaApiRouter);

module.exports = app;