import { NextRequest, NextResponse } from "next/server";
export async function POST(req: NextRequest){
  const body = await req.json().catch(()=>({}));
  // mock Twilio/WhatsApp Cloud API call
  return NextResponse.json({
    ok:true,
    provider:"mock-twilio-whatsapp",
    to: body.to || "+91 9xxxx x110",
    channel: body.channel || "WhatsApp",
    lang: body.lang || "mr",
    template_id: "krishi_hold_v1",
    status:"queued",
    cost_inr: 0.35,
    fallback: "SMS if not delivered in 2h, IVR for non-smartphone",
    message: "HOLD advice queued for 06:05 AM IST"
  });
}
export async function GET(){
  return NextResponse.json({ logs:[
    {id:"W-4821", status:"Read"}, {id:"W-4822", status:"Delivered"}
  ]});
}
