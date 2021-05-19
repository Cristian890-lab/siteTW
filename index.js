const express=require('express');
const fs=require('fs');
const sharp=require('sharp');
const {exec} = require("child_process");

const app = express();
const path = require("path");
app.set("view engine","ejs");
app.use("/resurse", express.static(path.join(__dirname,"resurse") ) );



app.get("/", function(req,res){
    let vector = verificaImagini();
    res.render("pagini/index", {ip:req.connection.remoteAddress,imagini:vector});
});

app.get("/index", function(req,res){
    let vector = verificaImagini();
    res.render("pagini/index", {ip:req.connection.remoteAddress,imagini:vector});
});

app.get("*/galeria-animata.css",function(req,res){
    res.setHeader("Content-Type","text/css");
    exec("sass resurse/sass/galeria-animata.scss temp/galeria-animata.css",(error, stderr, stdout) => {
        if (error) {
            return;
        }
        if (stderr) {
            return;
        }
        console.log('');
        res.sendFile(path.join(__dirname,"temp/galeria-animata.css"));
    });
});

app.get("/NewParts", function(req,res){
    let vector = verificaImagini();
    res.render("pagini/galerie-animata.ejs", {ip:req.connection.remoteAddress,imagini:vector});
});

app.get("/TopDeals", function(req,res){
    let vector = verificaImagini();
    res.render("pagini/galerie-statica", {ip:req.connection.remoteAddress,imagini:vector});
});

app.get("/Description", function(req,res){
    res.render("pagini/Description.ejs");
});

app.get("/galerie.json", function(req,res){
    res.render("pagini/403.ejs");
});

app.get("/Description", function(req,res){
    res.render("pagini/Guide.ejs");
});

app.get("/*",function(req,res){
    console.log(req.url)
    res.render("pagini"+req.url,function (err,rezultatRender){
        if(err){
            if(err.message.includes("Failed to lookup view")){
                res.status(404).render("pagini/ErrorPage")
            }
            else{
                throw err;
            }
        }
        else{
            res.send(rezultatRender);
        }

    });
});

function verificaImagini(){
    var textFisier=fs.readFileSync("resurse/json/galerie.json")
    var jsi=JSON.parse(textFisier);
    var caleGalerie=jsi.cale_galerie;
    let vectorCai=[]
    for(let im of jsi.imagini){
        var imVeche= path.join(caleGalerie, im.cale_imagine);
        var ext= path.extname(im.cale_imagine);
        var numeFisier= path.basename(im.cale_imagine,ext)
        let imNoua=path.join(caleGalerie+"/mic/",numeFisier+"-mic"+".webp");
        let imNouaMare=path.join(caleGalerie+"/mare/",numeFisier+"-mare"+".webp");

        if(!fs.existsSync(imNoua))
            sharp(imVeche)
                .resize(170,113)
                .toFile(imNoua,function (err){
                    if(err)
                        console.log("eroare conversie",imVeche,"->",imNoua,err);
                });

        if(!fs.existsSync(imNouaMare))
            sharp(imVeche)
                .resize(400,225)
                .toFile(imNouaMare,function (err){
                    if(err)
                        console.log("eroare conversie",imVeche,"->",imNouaMare,err);
                });

        vectorCai.push({mare:"/"+imNouaMare,mic:"/"+imNoua,titlu:im.titlu,sfert_ora:im.sfert_ora,text_descriere:im.descriere});
    }
    return vectorCai;

}


app.listen(8080);
console.log("merge, are picioare");