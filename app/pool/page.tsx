export default function Pool(){
  return (
    <div className="space-y-6">
      <div><h1 className="text-xl font-bold">FPO Pooling — The Headline Feature</h1><p className="text-sm text-gray-600">Aggregate 5-50 smallholder lots into 20-100 MT truck-loads. Bulk premium + shared logistics + single escrow. Most competitors build individual-farmer tools. We build collective bargaining.</p></div>
      <div className="grid md:grid-cols-3 gap-4">
        <div className="bg-krishi-600 text-white p-5 rounded-xl"><div className="text-sm opacity-90">Pilot: Solapur Tur Dal Cluster</div><div className="text-2xl font-bold mt-1">₹3.24L collective gain</div><div className="text-xs mt-1">23 farmers • 40 MT • ₹10,200/q vs ₹9,800/q solo</div><div className="mt-2 text-xs opacity-80">+₹110/q bulk premium + ₹43/q shared truck = ₹153/q net per farmer</div></div>
        <div className="bg-white p-5 rounded-xl border"><div className="text-sm text-gray-500">Avg Solo Sale (no pool)</div><div className="text-2xl font-bold">₹9,800/q</div><div className="text-xs text-gray-500 mt-1">10MT truck • ₹85/q transport • No negotiation power</div></div>
        <div className="bg-white p-5 rounded-xl border"><div className="text-sm text-gray-500">Pooled Sale (23 farmers)</div><div className="text-2xl font-bold text-green-700">₹10,200/q</div><div className="text-xs text-green-600 mt-1">40 MT truck • ₹42/q shared • Bulk premium + escrow split</div></div>
      </div>
      <div className="grid md:grid-cols-2 gap-6">
        <div className="bg-white p-5 rounded-xl border">
          <h3 className="font-semibold">Active Pool Request</h3>
          <div className="mt-3 p-3 bg-green-50 border border-green-200 rounded">
            <div className="flex justify-between items-start">
              <div><div className="font-medium">Onion — Junnar Cluster</div><div className="text-xs text-gray-500">Target: 25 MT by 31 Aug • Farmer count: 8 confirmed, 12 pending</div></div>
              <div className="text-right"><div className="font-bold text-green-700">18/25 MT</div><div className="text-xs text-gray-500">72% filled</div></div>
            </div>
            <div className="mt-2 w-full bg-gray-200 rounded-full h-2"><div className="bg-green-500 h-2 rounded-full" style={{width:"72%"}}></div></div>
            <div className="mt-2 text-xs text-gray-600">Buyer: Sahyadri Farms (verified) • ₹3,050/q (bulk) vs ₹2,850/q solo</div>
            <div className="flex gap-2 mt-2"><button className="bg-krishi-600 text-white px-3 py-1 rounded text-xs">Join Pool (+2MT onion)</button><button className="border px-3 py-1 rounded text-xs">View Members</button></div>
          </div>
          <div className="mt-3 text-xs text-gray-500 bg-gray-50 p-2 rounded">
            <div className="font-medium mb-1">How Pooling Works:</div>
            <div>1. Any farmer/FPO creates pool (set commodity, qty, target price, deadline)</div>
            <div>2. Nearby farmers join (auto-matched within 30km)</div>
            <div>3. When filled → shared truck booked (₹42/q vs ₹85/q solo)</div>
            <div>4. Buyer pays single escrow → split to each farmer's UPI</div>
            <div>5. Transparent ledger: each farmer sees their share in real-time</div>
          </div>
        </div>
        <div className="bg-white p-5 rounded-xl border">
          <h3 className="font-semibold">Pool Economics Calculator</h3>
          <div className="mt-3 space-y-3">
            <div className="grid grid-cols-2 gap-2 text-xs">
              <div><label className="text-gray-500">Your Qty (MT)</label><input type="number" defaultValue={5} className="w-full border rounded px-2 py-1 mt-1" /></div>
              <div><label className="text-gray-500">Commodity</label><select className="w-full border rounded px-2 py-1 mt-1"><option>Onion</option><option>Tur Dal</option><option>Soybean</option></select></div>
            </div>
            <div className="bg-gray-50 p-3 rounded text-xs space-y-1">
              <div className="flex justify-between"><span>Solo sale (current):</span><span className="font-bold">₹2,850/q × 5MT = ₹14,25,000</span></div>
              <div className="flex justify-between text-green-700"><span>Pooled sale (est):</span><span className="font-bold">₹3,050/q × 5MT = ₹15,25,000</span></div>
              <div className="flex justify-between border-t pt-1"><span>Your gain from pooling:</span><span className="font-bold text-green-700">+₹1,00,000 (+7%)</span></div>
              <div className="text-gray-500">Breakdown: +₹100/q bulk premium + ₹43/q shared truck + ₹0 negotiation (buyer verifies bulk)</div>
            </div>
            <button className="w-full bg-krishi-600 text-white py-2 rounded text-sm">Create Pool Request</button>
            <div className="text-[11px] text-gray-500">Pool size 20-100 MT. Minimum 5 farmers. Auto-alert to FPOs within 30km via WhatsApp.</div>
          </div>
        </div>
      </div>
      <div className="bg-white p-4 rounded-xl border">
        <h3 className="font-semibold text-sm">Why FPO Pooling is the Novelty Hook</h3>
        <div className="grid md:grid-cols-3 gap-3 text-xs mt-2">
          <div className="p-3 bg-gray-50 rounded"><b>vs Individual Alerts:</b> Most teams build price alerts for one farmer. We aggregate demand across 23 farmers to negotiate like one buyer. Collective bargaining = structural advantage, not information advantage.</div>
          <div className="p-3 bg-gray-50 rounded"><b>vs APMC Portals:</b> APMC shows prices but doesn't solve the "I have 2MT, buyer needs 50MT" gap. Pool bridges supply fragmentation.</div>
          <div className="p-3 bg-gray-50 rounded"><b>Judge hook:</b> "If 23 Solapur farmers pooled 40MT, they earned ₹3.24L more than solo. This scales to 14 lakh FPO farmers in Maharashtra."</div>
        </div>
      </div>
    </div>
  );
}
