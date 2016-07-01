//29/06/16
#include "Document.h"
#include <QString>
#include "DepluEntity.h"

Document::Document(QObject *parent) : QObject(parent){
}

void Document::parse(QString &&depluString){
}

void Document::clean(){
}

bool Document::setIter(int){
}

bool Document::hasNext(){
}

bool Document::isBool(){
}

bool Document::isString(){
}

bool Document::isFloat(){
}

bool Document::isDouble(){
}

bool Document::isInt(){
}

bool Document::isLong(){
}

bool Document::isNull(){
}

bool Document::isEmpty(){
}

bool Document::isArray(){
}

bool Document::isClass(){
}

bool Document::isAttrib(){
}

bool Document::isBool(QString member){
}

bool Document::isString(QString member){
}

bool Document::isFloat(QString member){
}

bool Document::isDouble(QString member){
}

bool Document::isInt(QString member){
}

bool Document::isLong(QString member){
}

bool Document::isNull(QString member){
}

bool Document::isEmpty(QString member){
}

weak_ptr<DepluEntity> Document::get(){
}

weak_ptr<DepluEntity> Document::operator[](int index){
}

bool Document::getBool(){
}

QString Document::getString(){
}

float Document::getFloat(){
}

double Document::getDouble(){
}

int Document::getInt(){
}

long Document::getLong(){
}

bool Document::getBool(QString member){
}

QString Document::getString(QString member){
}

float Document::getFloat(QString member){
}

double Document::getDouble(QString member){
}

int Document::getInt(QString member){
}

long Document::getLong(QString member){
}
