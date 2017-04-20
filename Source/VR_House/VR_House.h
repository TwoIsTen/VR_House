// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"

#define PRINT_ON_SCREEN(color, text, ...) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, color, FString::Printf(TEXT(text),##__VA_ARGS__))

DECLARE_LOG_CATEGORY_EXTERN(LogHouse, Log, All);