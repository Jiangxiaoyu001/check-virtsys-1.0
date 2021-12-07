package main

/* impotr package*/


import "C"
import (
    "fmt"
    "os"
)
/*
"io/ioutil"
    "encoding/xml"
*/
type XML interface{
    dealXml( string)
}

type xmlInfo struct{
}

func (_xml_ xmlInfo) dealXml(xml string){
    file,err:=os.Open(xml)
    if err!=nil{
        fmt.Println(err)
    }
    fmt.Println(file)
}

//export test
func test(){
    fmt.Println("hello go -tets")
}

//export _dealXml_
func _dealXml_(xml string){

    /*
    file,err:=os.Open(xml)
    if err!=nil{
        fmt.Println(err)
    }
    */
    _toXml_:=make([]byte,len(xml))
    copy(_toXml_,xml)
     toXml:=string(_toXml_)
    fmt.Printf("xml:%s len(toXml):%d",toXml,len(toXml))
}




func closePackage() func() (int, int) {
    number:=0
    var num int=5
    return func()(int,int ) {
        number++
        num--
        return number , num
    }
}




func main(){
/*
    var isxml XML
    isxml=new (xmlInfo)
    isxml.dealXml("")
    fmt.Println("xml. go")
  */
/*
  var hell string="hello world"
  test:="---test---"
  number:=10
  fmt.Println(test)
  fmt.Println(hell,number)
  */
  getpackage:=closePackage()
  for i:=0 ;i<5 ;i++{
      fmt.Println(getpackage());
 }
}















