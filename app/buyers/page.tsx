import { buyers } from "@/lib/mockData";
export default function Buyers(){
  return (
    <div className="space-y-4">
      <h1 className="text-xl font-bold">Verified Buyer Discovery & Matching</h1>
      <div className="flex gap-2 text-sm flex-wrap">
        <select className="border rounded px-2 py-1"><option>All Types</option><option>Processor</option><option>Exporter</option><option>Institutional</option></select>
        <select className="border rounded px-2 py-1"><option>Onion</option><option>Soybean</option><option>Tomato</option></select>
        <label className="flex items-center gap-1 text-xs"><input type="checkbox" defaultChecked /> Verified only</label>
        <span className="ml-auto text-xs text-gray-500">Matching: price + quality + qty + distance + payment history</span>
      </div>
      <div className="grid md:grid-cols-2 gap-4">
        {buyers.map(b=>(
          <div key={b.id} className="bg-white p-4 rounded-xl border">
            <div className="flex justify-between items-start">
              <div><div className="font-semibold text-sm flex gap-2 items-center">{b.name} {b.verified?<span className="bg-green-600 text-white text-[10px] px-1.5 py-0.5 rounded">✔ VERIFIED</span>:<span className="bg-gray-200 text-gray-600 text-[10px] px-1.5 py-0.5 rounded">Unverified</span>}</div><div className="text-xs text-gray-500">{b.type} • {b.location} • ⭐{b.rating} • 142 trades</div></div>
              <div className="text-right"><div className="font-bold">₹{b.offerPrice}/q</div><div className="text-xs text-gray-500">{b.requiredQty}q needed</div></div>
            </div>
            <div className="mt-2 text-xs bg-gray-50 p-2 rounded">Requires: <b>{b.commodity}</b> • {b.qualityGrade} • Payment: 48h UPI/RTGS • Logistics: buyer pickup</div>
            <div className="mt-2 flex gap-2 text-xs">
              <span className="bg-blue-50 text-blue-700 px-2 py-1 rounded">Credential: GST + FSSAI ✔</span>
              <span className="bg-green-50 text-green-700 px-2 py-1 rounded">On-time payment 96%</span>
            </div>
            <div className="mt-3 flex gap-2">
              <button className="flex-1 bg-krishi-600 text-white py-1.5 rounded text-xs">Send Offer (Negotiate)</button>
              <button className="flex-1 border py-1.5 rounded text-xs">View Profile & Reviews</button>
            </div>
          </div>
        ))}
      </div>
      <div className="bg-amber-50 p-3 rounded border text-xs">🔒 Trust Layer: Aadhaar + GST verification, trade history, peer ratings, escrow, and AI fraud flags. Unverified buyers are grey-listed until documents + 3 successful trades.</div>
    </div>
  );
}
