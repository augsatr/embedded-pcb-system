"use client";
import { useState } from "react";
import { alertLogs, channelStats, alertTemplates } from "@/lib/whatsapp";
import { advisory } from "@/lib/advisory";
export default function AlertPrefs(){
  const [sent,setSent]=useState(false);
  return (
    <div className="bg-white p-5 rounded-xl border space-y-3">
      <h3 className="font-bold flex gap-2">WhatsApp / SMS Layer — Real Deployability <span className="text-[10px] bg-green-600 text-white px-2 py-0.5 rounded-full">PILOT READY</span></h3>
      <p className="text-xs text-gray-600">{channelStats.whatsappPenetration}. Cost {channelStats.cost}. {channelStats.fallback}.</p>
      <div className="grid md:grid-cols-2 gap-3 text-xs">
        <div className="bg-green-50 border p-3 rounded">
          <div className="font-semibold">Next Auto-Alert (tomorrow 6:05 AM)</div>
          <div className="mt-2 font-mono bg-white p-2 rounded border text-[11px] leading-relaxed">{advisory.actionWhatsApp}</div>
          <div className="mt-2 flex gap-2">
            <button onClick={()=>setSent(true)} className="bg-green-600 text-white px-3 py-1.5 rounded text-xs">{sent?"Sent ✓":"Send Test WhatsApp"}</button>
            <select className="border rounded px-1"><option>मराठी</option><option>हिंदी</option><option>English</option></select>
          </div>
          <div className="mt-2 text-[11px] text-gray-500">Template: {alertTemplates.hold.slice(0,70)}… • Twilio/WhatsApp Cloud API • Opt-in per farmer</div>
          {sent && <div className="mt-2 text-green-700 bg-white p-1 rounded border text-[11px]">→ Mock API POST /api/alert {`{to:"+91...110", channel:"WhatsApp", lang:"mr"}`} 200 OK (see logs)</div>}
        </div>
        <div>
          <div className="font-semibold text-xs mb-1">Delivery Log (last 24h)</div>
          <table className="w-full text-[11px] border rounded">
            <thead className="bg-gray-50"><tr><th className="p-1 text-left">ID</th><th>Channel</th><th>Status</th><th>Lang</th></tr></thead>
            <tbody>{alertLogs.map(l=>(
              <tr key={l.id} className="border-t"><td className="p-1">{l.id}<div className="text-gray-400">{l.time}</div></td><td>{l.channel}</td><td><span className={`px-1 rounded ${l.status==="Read"?"bg-green-100 text-green-700":l.status==="Replied"?"bg-blue-100 text-blue-700":"bg-gray-100"}`}>{l.status}</span></td><td>{l.lang}</td></tr>
            ))}</tbody>
          </table>
          <div className="mt-2 flex gap-2">
            <label className="flex gap-1 items-center"><input type="checkbox" defaultChecked /> WhatsApp</label>
            <label className="flex gap-1 items-center"><input type="checkbox" defaultChecked /> SMS fallback</label>
            <label className="flex gap-1 items-center"><input type="checkbox" /> IVR Call</label>
          </div>
        </div>
      </div>
    </div>
  );
}
