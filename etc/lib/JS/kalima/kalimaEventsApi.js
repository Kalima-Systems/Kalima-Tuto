var fs=require("fs"),utils=require("./utils.js"),fileDir="",fifo="",currentEventFileName="",clients=[],kalimaEventsApi={init:function(e){fifo=(fileDir=e)+"/events_fifo",sendEventsFileName(),watchFile()},addClient(e,i){i.writeHead(200,{"Content-Type":"text/event-stream",Connection:"keep-alive","Cache-Control":"no-cache"});const n=Date.now();i={id:n,res:i};clients.push(i),e.on("close",()=>{clients=clients.filter(e=>e.id!==n)})}};function watchFile(){var n=fileDir+"/events/";fs.existsSync(n)||fs.mkdirSync(n,{recursive:!0}),fs.watch(n,function(e,i){i===currentEventFileName&&(fs.readFileSync(n+i,"utf8").split("\n").forEach(e=>{""!=e&&sendEvents(e)}),fs.unlinkSync(n+i),sendEventsFileName())})}function sendEvents(i){clients.forEach(e=>e.res.write(`data: ${i}

`))}function sendEventsFileName(){var e=utils.getRandomFileName();currentEventFileName=e,utils.writeFifo(fifo,"/?action=setEventsFileName&fileName="+e+"\n")}module.exports=kalimaEventsApi;