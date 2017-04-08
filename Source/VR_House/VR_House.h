// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"

#define PRINT_ON_SCREEN(text, ...) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White, FString::Printf(TEXT(text),##__VA_ARGS__))