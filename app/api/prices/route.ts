import { NextRequest, NextResponse } from "next/server";
import { fetchAgmarknet } from "@/lib/data/fetch";

export async function GET(req: NextRequest){
  const commodity = req.nextUrl.searchParams.get("commodity") || undefined;
  const state = req.nextUrl.searchParams.get("state") || "Maharashtra";
  const limit = Number(req.nextUrl.searchParams.get("limit") || "50");
  const result = await fetchAgmarknet({ commodity, state, limit });
  return NextResponse.json(result);
}
